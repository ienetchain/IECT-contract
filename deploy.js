var Vnt = require('vnt');
var vntkit = require('vnt-kit');
var fs = require("fs");
var Tx = require("ethereumjs-tx");

var conf = require("./conf.js");

var codeFile = conf.code;
var abi = JSON.parse(fs.readFileSync(conf.abi).toString("utf-8"));

var vnt = new Vnt();

vnt.setProvider(new vnt.providers.HttpProvider(conf.node));
var chainId=conf.chainId;

var ks = conf.keystore;
var password = conf.password;

function openAccount(file, passwd) {
    var content = fs.readFileSync(file).toString("utf-8");
    return vntkit.account.decrypt(content, passwd, false);
}

var account = openAccount(ks, password);

function deployWasmContract() {
  // 通过abi与代码路径初始化合约
  var contract = vnt.core.contract(abi).codeFile(codeFile)

  // 生成合约创建的数据
  var data = contract.packContructorData()

  // 获取账户1的下一个nonce值
  var nonce = vnt.core.getTransactionCount(account.address);

  // 生成交易的结构体，指定nonce, gasPirce, gasLimit, value, data等字段
  var options = {
     nonce: vnt.toHex(nonce),
     gasPrice: vnt.toHex(vnt.core.gasPrice),
     gasLimit: vnt.toHex(vnt.core.estimateGas({data: data})),
     // gasLimit: vnt.toHex(4000000),
     value: '0x00',
     data: data,
     chainId: chainId
  }

  console.log("options: ", options)

  // 生成交易
  var tx = new Tx(options);
  // 使用之前准备好的私钥，对交易签名
  tx.sign(new Buffer(account.privateKey.substring(2,), "hex"));

  // 将交易数据进行序列化
  var serializedTx = tx.serialize();

  // 发送交易
  vnt.core.sendRawTransaction('0x' + serializedTx.toString('hex'),
  function(err, txHash) {
    if (err) {
        console.log("err happened: ", err)
    } else {
        // 打印交易的hash
        console.log("transaction hash: ", txHash);
        // 获取交易的清单
        getTransactionReceipt(txHash, function(receipt) {
            console.log("tx receipt: ", receipt)
            console.log("tx status: ", receipt.status)
            console.log("contract address: ", receipt.contractAddress)
        })
    }
  });
}

function getTransactionReceipt(tx, cb) {
  var receipt = vnt.core.getTransactionReceipt(tx)
  if(!receipt) {
      setTimeout(function () {
          getTransactionReceipt(tx, cb)
      }, 1000);
  } else {
      cb(receipt)
  }
}

deployWasmContract()
