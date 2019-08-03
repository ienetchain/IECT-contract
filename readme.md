# TOKEN IECT

## 一、IECT代币的参数
* 发行量`totalSupply`：20亿
* 精度`decimals`：18
* 代币名称`name`：IECT
* 代币符号`symbol`：IECT

## 二、IECT接口
### 1.构造函数：`TokenERC20`
* 作用：合约创建时被调用，用于初始化代币默认配置
* 参数：无
* 返回：无
* 失败的条件(按顺序)
  - 无
* 成功后的状态变化
  - owner被设置为from
  - balance\[owner\] = totalsupply



### 2.`transfer`

* 类型：Mutable
* 作用：代币转账，将_value数量的代币从from地址发送到_\_to地址，其中from为转账交易的发起人
* 参数：
  - \_to：address类型，代币转账的接收账号
  - \_value：uint256类型，代币转账的金额
* 返回：
  - output：bool类型，表示是否转账成功
* 失败的条件(按顺序)
  - 代币被锁定(restricted == true)
  - 发币账户被锁定(restriction\[from\] = true)
  - 收币账户被锁定(restriction\[to\] = true)
  - \_to为0x0空地址
  - from地址的余额小于_value
  - \_to的余额加上\_value后溢出256位整形
* 成功后的状态变化
  - from的余额被减少\_value
  - \_to的余额被增加\_value
  - 记录一条Transfer日志

### 3.`approve`

* 类型：Mutable
* 作用：分配子账户份额的，允许将_value数据的代币分配给\_spender消费
* 参数：
  * \_spender：address类型，子账户的地址
  * \_value：uint256类型，允许的份额
* 返回：‘
  * output：bool类型，表示是否分配成功
* 失败的条件(按顺序)
  * 无
* 成功后的状态变化
  * allowance\[from\]\[\_spender\] = \_value
  * 记录一条Approval日志

### 4.`transferFrom`

* 类型：Mutable
* 作用：子账户转账，子账户从父账户\_from的余额中，直接转账\_value金额给\_to地址
* 参数
  * \_from：address类型，父账户的地址
  * \_to：address类型，转账的接收地址
  * \_value：uint256类型，转账的金额
* 返回：
  * output：bool类型，是否转账成功
* 失败的条件(按顺序)
  * from被锁定(restriction\[from\] = true)
  * 子账户的份额：allowance\[\_from\]\[from\]小于\_value
  * 代币被锁定(restricted == true)
  * 发币账户被锁定(restriction\[\_from\] = true)
  * 收币账户被锁定(restriction\[\_to\] = true)
  * \_to为0x0空地址
  * \_from地址的余额小于_value
  * \_to的余额加上\_value后溢出256位整形
* 成功后的状态变化
  * allowance\[\_from]\[from]减少\_value
  * \_from的余额被减少\_value
  * \_to的余额被增加\_value
  * from的余额不变
  * 记录一条Transfer日志

### 5.`editRestricted`

- 类型：Mutable
- 作用：修改合约的全局锁定状态
- 参数：
  - 无
- 返回
  - output：bool类型，表示是否修改成功
- 失败的条件(按顺序)
  - 交易的发起者from != owner
- 成功后的状态变化
  - restricted取反



### 6.`editRestrictedAddress`

- 类型：Mutable
- 作用：修改合约某个账户的锁定状态
- 参数：
  - \_addr：address类型，修改的地址
- 返回
  - output：bool类型，表示是否修改成功
- 失败的条件(按顺序)
  - 交易的发起者from != owner
- 成功后的状态变化
  - restriction\[\_addr]取反



### 7.`isRestricted`

- 类型：Unmutable
- 作用：检查合约整体的锁定状态
- 参数：
  - 无
- 返回
  - output：bool类型，表示是否被锁定
- 失败的条件(按顺序)
  - 无
- 成功后的状态变化
  - 无

### 8.`isRestrictedAddress`

- 类型：Unmutable
- 作用：检查某个账户的锁定状态
- 参数：
  - \_addr：address类型，要检查的地址
- 返回
  - output：bool类型，表示是否被锁定
- 失败的条件(按顺序)
  - 无
- 成功后的状态变化
  - 无

### 9.`allowance`

- 类型：Unmutable
- 作用：检查子账户的余额
- 参数：
  - \_owner：address类型，要检查的主地址
  - _spender：address类型，要检查的子地址
- 返回
  - output：uint256类型，表示子账户的余额
- 失败的条件(按顺序)
  - 如果没有余额，返回是0
- 成功后的状态变化
  - 无

### 10.`GetTokenName`

- 类型：Unmutable
- 作用：获取代币的名称，也就是name的值
- 参数：
  - 无
- 返回
  - output：string类型，代币的名字
- 失败的条件(按顺序)
  - 无
- 成功后的状态变化
  - 无

### 11.`GetTotalSupply`

- 类型：Unmutable
- 作用：获取代币的发行量，也就是totalSupply的值
- 参数：
  - 无
- 返回
  - output：uint256类型，代币的发行量
- 失败的条件(按顺序)
  - 无
- 成功后的状态变化
  - 无

### 12.`GetDecimals`

- 类型：Unmutable
- 作用：获取代币的精度，也就是decimals的值
- 参数：
  - 无
- 返回
  - output：uint256类型，代币的精度
- 失败的条件(按顺序)
  - 无
- 成功后的状态变化
  - 无

### 13.`GetSymbol`

- 类型：Unmutable
- 作用：获取代币的符号，也就是symbol的值
- 参数：
  - 无
- 返回
  - output：string类型，代币的符号
- 失败的条件(按顺序)
  - 无
- 成功后的状态变化
  - 无

### 14.`GetAmount`

- 类型：Unmutable
- 作用：获取某个账号的代币余额
- 参数：
  - addr：address类型
- 返回
  - output：uint256类型，代币的余额
- 失败的条件(按顺序)
  - 无
- 成功后的状态变化
  - 无

### 15.事件`Transfer`

- 类型：事件
- 作用：记录一条转账事件
- 参数：
  - from：address类型，转账发起人
  - to：address类型，转账接收人
  - value：uint256类型，转账金额
- 返回
  - 无
- 失败的条件(按顺序)
  - 无
- 成功后的状态变化
  - 增加了一条日志

### 16.事件`Approval`

- 类型：事件
- 作用：记录一条子账号分配的事件
- 参数：
  - owner：address类型，父账号的地址
  - spender：address类型，子账号的地址
  - value：uint256类型，分配的金额
- 返回
  - 无
- 失败的条件(按顺序)
  - 无
- 成功后的状态变化
  - 增加了一条日志



# 使用方法

## 编译合约

```
cd contract
bottle compile --code iect.c --output . --include .
```

编译完成后，会得到如下输出

```
Compile contract: IECT
=======================
Input file
===========
   > Contract path:           iect.c
Output file
============
   > Abi path:                IECT.abi
   > Precompile code path:    IECT_precompile.c
   > Wasm path:               IECT.wasm
   > Compress data path:      IECT.compress
   > Compress hex Data path:  IECT.hex
   > Deploy js path:          IECT.js
   > Contract json path:      IECT.json
   > Please use IECT.compress when you want to create a contract
Compile finished. 114.905413ms
===============================
```

会在contract目录中生成数个文件，其中IECT.compress和IECT.abi是我们需要用到的



## 准备keystore

需要准备一个账户，用来发起交易。我们需要把它的keystore文件放到keystore目录下。



## 修改配置

修改conf.js

```
module.exports = {
  node: "https://hubscan.vnt.link/rpc",  //rpc地址
  chainId: 2, // chain id
  keystore: "keystore/keystore.json",  //用来部署合约的账户keystore
  password: "****",  //用来解密keystore的密码
  code: "contract/IECT.compress",  //合约代码
  abi: "contract/IECT.abi", //合约abi
}
```



## 安装依赖

```
npm install
```


## 部署

```
node deploy.js
```

执行完成后， terminal中会打印合约的地址
