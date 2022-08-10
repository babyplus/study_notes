# 数据库中所有的表

```
mysql> SELECT table_name , table_comment  FROM information_schema.TABLES WHERE table_schema = 'jsh_erp';
+----------------------------+-------------------------------+
| table_name                 | table_comment                 |
+----------------------------+-------------------------------+
| jsh_account                | 账户信息                      |
| jsh_account_head           | 财务主表                      |
| jsh_account_item           | 财务子表                      |
| jsh_depot                  | 仓库表                        |
| jsh_depot_head             | 单据主表                      |
| jsh_depot_item             | 单据子表                      |
| jsh_function               | 功能模块表                    |
| jsh_in_out_item            | 收支项目                      |
| jsh_log                    | 操作日志                      |
| jsh_material               | 产品表                        |
| jsh_material_attribute     | 产品属性表                    |
| jsh_material_category      | 产品类型表                    |
| jsh_material_current_stock | 产品当前库存                  |
| jsh_material_extend        | 产品价格扩展                  |
| jsh_material_initial_stock | 产品初始库存                  |
| jsh_material_property      | 产品扩展字段表                |
| jsh_msg                    | 消息表                        |
| jsh_orga_user_rel          | 机构用户关系表                |
| jsh_organization           | 机构表                        |
| jsh_person                 | 经手人表                      |
| jsh_platform_config        | 平台参数                      |
| jsh_role                   | 角色表                        |
| jsh_sequence               | 单据编号表                    |
| jsh_serial_number          | 序列号表                      |
| jsh_supplier               | 供应商/客户信息表             |
| jsh_system_config          | 系统参数                      |
| jsh_tenant                 | 租户                          |
| jsh_unit                   | 多单位表                      |
| jsh_user                   | 用户表                        |
| jsh_user_business          | 用户/角色/模块关系表          |
+----------------------------+-------------------------------+
30 rows in set (0.00 sec)

```

# 数据库表结构

## jsh_account 账户信息

```
+----------------+------------+---------------+----------------+-------------------------------------+
| COLUMN_NAME    | column_key | column_type   | extra          | column_comment                      |
+----------------+------------+---------------+----------------+-------------------------------------+
| id             | PRI        | bigint(20)    | auto_increment | 主键                                |
| name           |            | varchar(50)   |                | 名称                                |
| serial_no      |            | varchar(50)   |                | 编号                                |
| initial_amount |            | decimal(24,6) |                | 期初金额                            |
| current_amount |            | decimal(24,6) |                | 当前余额                            |
| remark         |            | varchar(100)  |                | 备注                                |
| is_default     |            | bit(1)        |                | 是否默认                            |
| tenant_id      |            | bigint(20)    |                | 租户id                              |
| delete_flag    |            | varchar(1)    |                | 删除标记，0未删除，1删除            |
+----------------+------------+---------------+----------------+-------------------------------------+
```

## jsh_account_head 财务主表

```
+-----------------+------------+---------------+----------------+--------------------------------------------+
| COLUMN_NAME     | column_key | column_type   | extra          | column_comment                             |
+-----------------+------------+---------------+----------------+--------------------------------------------+
| id              | PRI        | bigint(20)    | auto_increment | 主键                                       |
| type            |            | varchar(50)   |                | 类型(支出/收入/收款/付款/转账)             |
| organ_id        | MUL        | bigint(20)    |                | 单位Id(收款/付款单位)                      |
| hands_person_id | MUL        | bigint(20)    |                | 经手人id                                   |
| creator         |            | bigint(20)    |                | 操作员                                     |
| change_amount   |            | decimal(24,6) |                | 变动金额(优惠/收款/付款/实付)              |
| discount_money  |            | decimal(24,6) |                | 优惠金额                                   |
| total_price     |            | decimal(24,6) |                | 合计金额                                   |
| account_id      | MUL        | bigint(20)    |                | 账户(收款/付款)                            |
| bill_no         |            | varchar(50)   |                | 单据编号                                   |
| bill_time       |            | datetime      |                | 单据日期                                   |
| remark          |            | varchar(100)  |                | 备注                                       |
| file_name       |            | varchar(500)  |                | 附件名称                                   |
| status          |            | varchar(1)    |                | 状态，0未审核、1已审核                     |
| tenant_id       |            | bigint(20)    |                | 租户id                                     |
| delete_flag     |            | varchar(1)    |                | 删除标记，0未删除，1删除                   |
+-----------------+------------+---------------+----------------+--------------------------------------------+
```

## jsh_account_item 财务子表

```
+----------------+------------+---------------+----------------+-------------------------------------+
| COLUMN_NAME    | column_key | column_type   | extra          | column_comment                      |
+----------------+------------+---------------+----------------+-------------------------------------+
| id             | PRI        | bigint(20)    | auto_increment | 主键                                |
| header_id      | MUL        | bigint(20)    |                | 表头Id                              |
| account_id     | MUL        | bigint(20)    |                | 账户Id                              |
| in_out_item_id | MUL        | bigint(20)    |                | 收支项目Id                          |
| bill_id        |            | bigint(20)    |                | 单据id                              |
| need_debt      |            | decimal(24,6) |                | 应收欠款                            |
| finish_debt    |            | decimal(24,6) |                | 已收欠款                            |
| each_amount    |            | decimal(24,6) |                | 单项金额                            |
| remark         |            | varchar(100)  |                | 单据备注                            |
| tenant_id      |            | bigint(20)    |                | 租户id                              |
| delete_flag    |            | varchar(1)    |                | 删除标记，0未删除，1删除            |
+----------------+------------+---------------+----------------+-------------------------------------+
```

## jsh_depot 仓库表

```
+-------------+------------+---------------+----------------+-------------------------------------+
| COLUMN_NAME | column_key | column_type   | extra          | column_comment                      |
+-------------+------------+---------------+----------------+-------------------------------------+
| id          | PRI        | bigint(20)    | auto_increment | 主键                                |
| name        |            | varchar(20)   |                | 仓库名称                            |
| address     |            | varchar(50)   |                | 仓库地址                            |
| warehousing |            | decimal(24,6) |                | 仓储费                              |
| truckage    |            | decimal(24,6) |                | 搬运费                              |
| type        |            | int(10)       |                | 类型                                |
| sort        |            | varchar(10)   |                | 排序                                |
| remark      |            | varchar(100)  |                | 描述                                |
| principal   |            | bigint(20)    |                | 负责人                              |
| tenant_id   |            | bigint(20)    |                | 租户id                              |
| delete_Flag |            | varchar(1)    |                | 删除标记，0未删除，1删除            |
| is_default  |            | bit(1)        |                | 是否默认                            |
+-------------+------------+---------------+----------------+-------------------------------------+
```

## jsh_depot_head 单据主表

```
+---------------------+------------+---------------+----------------+--------------------------------------------------------------------------------+
| COLUMN_NAME         | column_key | column_type   | extra          | column_comment                                                                 |
+---------------------+------------+---------------+----------------+--------------------------------------------------------------------------------+
| id                  | PRI        | bigint(20)    | auto_increment | 主键                                                                           |
| type                |            | varchar(50)   |                | 类型(出库/入库)                                                                |
| sub_type            |            | varchar(50)   |                | 出入库分类                                                                     |
| default_number      |            | varchar(50)   |                | 初始票据号                                                                     |
| number              |            | varchar(50)   |                | 票据号                                                                         |
| create_time         |            | datetime      |                | 创建时间                                                                       |
| oper_time           |            | datetime      |                | 出入库时间                                                                     |
| organ_id            | MUL        | bigint(20)    |                | 供应商id                                                                       |
| creator             |            | bigint(20)    |                | 操作员                                                                         |
| account_id          | MUL        | bigint(20)    |                | 账户id                                                                         |
| change_amount       |            | decimal(24,6) |                | 变动金额(收款/付款)                                                            |
| back_amount         |            | decimal(24,6) |                | 找零金额                                                                       |
| total_price         |            | decimal(24,6) |                | 合计金额                                                                       |
| pay_type            |            | varchar(50)   |                | 付款类型(现金、记账等)                                                         |
| bill_type           |            | varchar(50)   |                | 单据类型                                                                       |
| remark              |            | varchar(1000) |                | 备注                                                                           |
| file_name           |            | varchar(500)  |                | 附件名称                                                                       |
| sales_man           |            | varchar(50)   |                | 业务员（可以多个）                                                             |
| account_id_list     |            | varchar(50)   |                | 多账户ID列表                                                                   |
| account_money_list  |            | varchar(200)  |                | 多账户金额列表                                                                 |
| discount            |            | decimal(24,6) |                | 优惠率                                                                         |
| discount_money      |            | decimal(24,6) |                | 优惠金额                                                                       |
| discount_last_money |            | decimal(24,6) |                | 优惠后金额                                                                     |
| other_money         |            | decimal(24,6) |                | 销售或采购费用合计                                                             |
| deposit             |            | decimal(24,6) |                | 订金                                                                           |
| status              |            | varchar(1)    |                | 状态，0未审核、1已审核、2完成采购|销售、3部分采购|销售                         |
| purchase_status     |            | varchar(1)    |                | 采购状态，0未采购、2完成采购、3部分采购                                        |
| link_number         |            | varchar(50)   |                | 关联订单号                                                                     |
| tenant_id           |            | bigint(20)    |                | 租户id                                                                         |
| delete_flag         |            | varchar(1)    |                | 删除标记，0未删除，1删除                                                       |
+---------------------+------------+---------------+----------------+--------------------------------------------------------------------------------+
```

## jsh_depot_item 单据子表

```
+--------------------+------------+---------------+----------------+-------------------------------------+
| COLUMN_NAME        | column_key | column_type   | extra          | column_comment                      |
+--------------------+------------+---------------+----------------+-------------------------------------+
| id                 | PRI        | bigint(20)    | auto_increment | 主键                                |
| header_id          | MUL        | bigint(20)    |                | 表头Id                              |
| material_id        | MUL        | bigint(20)    |                | 商品Id                              |
| material_extend_id |            | bigint(20)    |                | 商品扩展id                          |
| material_unit      |            | varchar(20)   |                | 商品计量单位                        |
| sku                |            | varchar(50)   |                | 多属性                              |
| oper_number        |            | decimal(24,6) |                | 数量                                |
| basic_number       |            | decimal(24,6) |                | 基础数量，如kg、瓶                  |
| unit_price         |            | decimal(24,6) |                | 单价                                |
| tax_unit_price     |            | decimal(24,6) |                | 含税单价                            |
| all_price          |            | decimal(24,6) |                | 金额                                |
| remark             |            | varchar(200)  |                | 备注                                |
| depot_id           | MUL        | bigint(20)    |                | 仓库ID                              |
| another_depot_id   | MUL        | bigint(20)    |                | 调拨时，对方仓库Id                  |
| tax_rate           |            | decimal(24,6) |                | 税率                                |
| tax_money          |            | decimal(24,6) |                | 税额                                |
| tax_last_money     |            | decimal(24,6) |                | 价税合计                            |
| material_type      |            | varchar(20)   |                | 商品类型                            |
| sn_list            |            | varchar(2000) |                | 序列号列表                          |
| batch_number       |            | varchar(100)  |                | 批号                                |
| expiration_date    |            | datetime      |                | 有效日期                            |
| link_id            |            | bigint(20)    |                | 关联明细id                          |
| tenant_id          |            | bigint(20)    |                | 租户id                              |
| delete_flag        |            | varchar(1)    |                | 删除标记，0未删除，1删除            |
+--------------------+------------+---------------+----------------+-------------------------------------+
```

## jsh_function 功能模块表

```
+---------------+------------+--------------+----------------+-------------------------------------+
| COLUMN_NAME   | column_key | column_type  | extra          | column_comment                      |
+---------------+------------+--------------+----------------+-------------------------------------+
| id            | PRI        | bigint(20)   | auto_increment | 主键                                |
| number        |            | varchar(50)  |                | 编号                                |
| name          |            | varchar(50)  |                | 名称                                |
| parent_number |            | varchar(50)  |                | 上级编号                            |
| url           | UNI        | varchar(100) |                | 链接                                |
| component     |            | varchar(100) |                | 组件                                |
| state         |            | bit(1)       |                | 收缩                                |
| sort          |            | varchar(50)  |                | 排序                                |
| enabled       |            | bit(1)       |                | 启用                                |
| type          |            | varchar(50)  |                | 类型                                |
| push_btn      |            | varchar(50)  |                | 功能按钮                            |
| icon          |            | varchar(50)  |                | 图标                                |
| delete_flag   |            | varchar(1)   |                | 删除标记，0未删除，1删除            |
+---------------+------------+--------------+----------------+-------------------------------------+
```

## jsh_in_out_item 收支项目

```
+-------------+------------+--------------+----------------+-------------------------------------+
| COLUMN_NAME | column_key | column_type  | extra          | column_comment                      |
+-------------+------------+--------------+----------------+-------------------------------------+
| id          | PRI        | bigint(20)   | auto_increment | 主键                                |
| name        |            | varchar(50)  |                | 名称                                |
| type        |            | varchar(20)  |                | 类型                                |
| remark      |            | varchar(100) |                | 备注                                |
| tenant_id   |            | bigint(20)   |                | 租户id                              |
| delete_flag |            | varchar(1)   |                | 删除标记，0未删除，1删除            |
+-------------+------------+--------------+----------------+-------------------------------------+
```

## jsh_log 操作日志

```
+-------------+------------+---------------+----------------+------------------------------------+
| COLUMN_NAME | column_key | column_type   | extra          | column_comment                     |
+-------------+------------+---------------+----------------+------------------------------------+
| id          | PRI        | bigint(20)    | auto_increment | 主键                               |
| user_id     | MUL        | bigint(20)    |                | 用户id                             |
| operation   |            | varchar(500)  |                | 操作模块名称                       |
| client_ip   |            | varchar(200)  |                | 客户端IP                           |
| create_time |            | datetime      |                | 创建时间                           |
| status      |            | tinyint(4)    |                | 操作状态 0==成功，1==失败          |
| content     |            | varchar(1000) |                | 详情                               |
| tenant_id   |            | bigint(20)    |                | 租户id                             |
+-------------+------------+---------------+----------------+------------------------------------+
```

## jsh_material 产品表

```
+----------------------+------------+---------------+----------------+-------------------------------------+
| COLUMN_NAME          | column_key | column_type   | extra          | column_comment                      |
+----------------------+------------+---------------+----------------+-------------------------------------+
| id                   | PRI        | bigint(20)    | auto_increment | 主键                                |
| category_id          | MUL        | bigint(20)    |                | 产品类型id                          |
| name                 |            | varchar(100)  |                | 名称                                |
| mfrs                 |            | varchar(50)   |                | 制造商                              |
| model                |            | varchar(50)   |                | 型号                                |
| standard             |            | varchar(50)   |                | 规格                                |
| color                |            | varchar(50)   |                | 颜色                                |
| unit                 |            | varchar(50)   |                | 单位-单个                           |
| remark               |            | varchar(100)  |                | 备注                                |
| img_name             |            | varchar(500)  |                | 图片名称                            |
| unit_id              | MUL        | bigint(20)    |                | 计量单位Id                          |
| expiry_num           |            | int(10)       |                | 保质期天数                          |
| weight               |            | decimal(24,6) |                | 基础重量(kg)                        |
| enabled              |            | bit(1)        |                | 启用 0-禁用  1-启用                 |
| other_field1         |            | varchar(50)   |                | 自定义1                             |
| other_field2         |            | varchar(50)   |                | 自定义2                             |
| other_field3         |            | varchar(50)   |                | 自定义3                             |
| enable_serial_number |            | varchar(1)    |                | 是否开启序列号，0否，1是            |
| enable_batch_number  |            | varchar(1)    |                | 是否开启批号，0否，1是              |
| tenant_id            |            | bigint(20)    |                | 租户id                              |
| delete_flag          |            | varchar(1)    |                | 删除标记，0未删除，1删除            |
+----------------------+------------+---------------+----------------+-------------------------------------+
```

## jsh_material_attribute 产品属性表

```
+-----------------+------------+--------------+----------------+-------------------------------------+
| COLUMN_NAME     | column_key | column_type  | extra          | column_comment                      |
+-----------------+------------+--------------+----------------+-------------------------------------+
| id              | PRI        | bigint(20)   | auto_increment |                                     |
| attribute_field |            | varchar(50)  |                | 属性字段                            |
| attribute_name  |            | varchar(50)  |                | 属性名                              |
| attribute_value |            | varchar(500) |                | 属性值                              |
| tenant_id       |            | bigint(20)   |                | 租户id                              |
| delete_flag     |            | varchar(1)   |                | 删除标记，0未删除，1删除            |
+-----------------+------------+--------------+----------------+-------------------------------------+
```

## jsh_material_category 产品类型表

```
+----------------+------------+---------------+----------------+-------------------------------------+
| COLUMN_NAME    | column_key | column_type   | extra          | column_comment                      |
+----------------+------------+---------------+----------------+-------------------------------------+
| id             | PRI        | bigint(20)    | auto_increment | 主键                                |
| name           |            | varchar(50)   |                | 名称                                |
| category_level |            | smallint(6)   |                | 等级                                |
| parent_id      | MUL        | bigint(20)    |                | 上级id                              |
| sort           |            | varchar(10)   |                | 显示顺序                            |
| serial_no      |            | varchar(100)  |                | 编号                                |
| remark         |            | varchar(1024) |                | 备注                                |
| create_time    |            | datetime      |                | 创建时间                            |
| update_time    |            | datetime      |                | 更新时间                            |
| tenant_id      |            | bigint(20)    |                | 租户id                              |
| delete_flag    |            | varchar(1)    |                | 删除标记，0未删除，1删除            |
+----------------+------------+---------------+----------------+-------------------------------------+
```

## jsh_material_current_stock 产品当前库存

```
+----------------+------------+---------------+----------------+-------------------------------------+
| COLUMN_NAME    | column_key | column_type   | extra          | column_comment                      |
+----------------+------------+---------------+----------------+-------------------------------------+
| id             | PRI        | bigint(20)    | auto_increment | 主键                                |
| material_id    |            | bigint(20)    |                | 产品id                              |
| depot_id       |            | bigint(20)    |                | 仓库id                              |
| current_number |            | decimal(24,6) |                | 当前库存数量                        |
| tenant_id      |            | bigint(20)    |                | 租户id                              |
| delete_flag    |            | varchar(1)    |                | 删除标记，0未删除，1删除            |
+----------------+------------+---------------+----------------+-------------------------------------+
```

## jsh_material_extend 产品价格扩展

```
+-------------------+------------+---------------+----------------+-------------------------------------+
| COLUMN_NAME       | column_key | column_type   | extra          | column_comment                      |
+-------------------+------------+---------------+----------------+-------------------------------------+
| id                | PRI        | bigint(20)    | auto_increment | 主键                                |
| material_id       |            | bigint(20)    |                | 商品id                              |
| bar_code          |            | varchar(50)   |                | 商品条码                            |
| commodity_unit    |            | varchar(50)   |                | 商品单位                            |
| sku               |            | varchar(50)   |                | 多属性                              |
| purchase_decimal  |            | decimal(24,6) |                | 采购价格                            |
| commodity_decimal |            | decimal(24,6) |                | 零售价格                            |
| wholesale_decimal |            | decimal(24,6) |                | 销售价格                            |
| low_decimal       |            | decimal(24,6) |                | 最低售价                            |
| default_flag      |            | varchar(1)    |                | 是否为默认单位，1是，0否            |
| create_time       |            | datetime      |                | 创建日期                            |
| create_serial     |            | varchar(50)   |                | 创建人编码                          |
| update_serial     |            | varchar(50)   |                | 更新人编码                          |
| update_time       |            | bigint(20)    |                | 更新时间戳                          |
| tenant_id         |            | bigint(20)    |                | 租户id                              |
| delete_Flag       |            | varchar(1)    |                | 删除标记，0未删除，1删除            |
+-------------------+------------+---------------+----------------+-------------------------------------+
```

## jsh_material_initial_stock 产品初始库存

```
+-----------------+------------+---------------+----------------+-------------------------------------+
| COLUMN_NAME     | column_key | column_type   | extra          | column_comment                      |
+-----------------+------------+---------------+----------------+-------------------------------------+
| id              | PRI        | bigint(20)    | auto_increment | 主键                                |
| material_id     |            | bigint(20)    |                | 产品id                              |
| depot_id        |            | bigint(20)    |                | 仓库id                              |
| number          |            | decimal(24,6) |                | 初始库存数量                        |
| low_safe_stock  |            | decimal(24,6) |                | 最低库存数量                        |
| high_safe_stock |            | decimal(24,6) |                | 最高库存数量                        |
| tenant_id       |            | bigint(20)    |                | 租户id                              |
| delete_flag     |            | varchar(1)    |                | 删除标记，0未删除，1删除            |
+-----------------+------------+---------------+----------------+-------------------------------------+
```

## jsh_material_property 产品扩展字段表

```
+--------------+------------+-------------+----------------+-------------------------------------+
| COLUMN_NAME  | column_key | column_type | extra          | column_comment                      |
+--------------+------------+-------------+----------------+-------------------------------------+
| id           | PRI        | bigint(20)  | auto_increment | 主键                                |
| native_name  |            | varchar(50) |                | 原始名称                            |
| enabled      |            | bit(1)      |                | 是否启用                            |
| sort         |            | varchar(10) |                | 排序                                |
| another_name |            | varchar(50) |                | 别名                                |
| delete_flag  |            | varchar(1)  |                | 删除标记，0未删除，1删除            |
+--------------+------------+-------------+----------------+-------------------------------------+
```

## jsh_msg 消息表

```
+-------------+------------+--------------+----------------+-------------------------------------+
| COLUMN_NAME | column_key | column_type  | extra          | column_comment                      |
+-------------+------------+--------------+----------------+-------------------------------------+
| id          | PRI        | bigint(20)   | auto_increment | 主键                                |
| msg_title   |            | varchar(100) |                | 消息标题                            |
| msg_content |            | varchar(500) |                | 消息内容                            |
| create_time |            | datetime     |                | 创建时间                            |
| type        |            | varchar(20)  |                | 消息类型                            |
| status      |            | varchar(1)   |                | 状态，1未读 2已读                   |
| tenant_id   |            | bigint(20)   |                | 租户id                              |
| delete_Flag |            | varchar(1)   |                | 删除标记，0未删除，1删除            |
+-------------+------------+--------------+----------------+-------------------------------------+
```

## jsh_orga_user_rel 机构用户关系表

```
+-------------------------+------------+-------------+----------------+--------------------------------------+
| COLUMN_NAME             | column_key | column_type | extra          | column_comment                       |
+-------------------------+------------+-------------+----------------+--------------------------------------+
| id                      | PRI        | bigint(20)  | auto_increment | 主键                                 |
| orga_id                 |            | bigint(20)  |                | 机构id                               |
| user_id                 |            | bigint(20)  |                | 用户id                               |
| user_blng_orga_dspl_seq |            | varchar(20) |                | 用户在所属机构中显示顺序             |
| delete_flag             |            | char(1)     |                | 删除标记，0未删除，1删除             |
| create_time             |            | datetime    |                | 创建时间                             |
| creator                 |            | bigint(20)  |                | 创建人                               |
| update_time             |            | datetime    |                | 更新时间                             |
| updater                 |            | bigint(20)  |                | 更新人                               |
| tenant_id               |            | bigint(20)  |                | 租户id                               |
+-------------------------+------------+-------------+----------------+--------------------------------------+
```

## jsh_organization 机构表

```
+-------------+------------+--------------+----------------+-------------------------------------+
| COLUMN_NAME | column_key | column_type  | extra          | column_comment                      |
+-------------+------------+--------------+----------------+-------------------------------------+
| id          | PRI        | bigint(20)   | auto_increment | 主键                                |
| org_no      |            | varchar(20)  |                | 机构编号                            |
| org_abr     |            | varchar(20)  |                | 机构简称                            |
| parent_id   |            | bigint(20)   |                | 父机构id                            |
| sort        |            | varchar(20)  |                | 机构显示顺序                        |
| remark      |            | varchar(500) |                | 备注                                |
| create_time |            | datetime     |                | 创建时间                            |
| update_time |            | datetime     |                | 更新时间                            |
| tenant_id   |            | bigint(20)   |                | 租户id                              |
| delete_flag |            | varchar(1)   |                | 删除标记，0未删除，1删除            |
+-------------+------------+--------------+----------------+-------------------------------------+
```

## jsh_person 经手人表

```
+-------------+------------+-------------+----------------+-------------------------------------+
| COLUMN_NAME | column_key | column_type | extra          | column_comment                      |
+-------------+------------+-------------+----------------+-------------------------------------+
| id          | PRI        | bigint(20)  | auto_increment | 主键                                |
| type        |            | varchar(20) |                | 类型                                |
| name        |            | varchar(50) |                | 姓名                                |
| tenant_id   |            | bigint(20)  |                | 租户id                              |
| delete_flag |            | varchar(1)  |                | 删除标记，0未删除，1删除            |
+-------------+------------+-------------+----------------+-------------------------------------+
```

## jsh_platform_config 平台参数

```
+-------------------+------------+--------------+----------------+-----------------+
| COLUMN_NAME       | column_key | column_type  | extra          | column_comment  |
+-------------------+------------+--------------+----------------+-----------------+
| id                | PRI        | bigint(20)   | auto_increment |                 |
| platform_key      |            | varchar(100) |                | 关键词          |
| platform_key_info |            | varchar(100) |                | 关键词名称      |
| platform_value    |            | varchar(200) |                | 值              |
+-------------------+------------+--------------+----------------+-----------------+
```

## jsh_role 角色表

```
+-------------+------------+--------------+----------------+-------------------------------------+
| COLUMN_NAME | column_key | column_type  | extra          | column_comment                      |
+-------------+------------+--------------+----------------+-------------------------------------+
| id          | PRI        | bigint(20)   | auto_increment | 主键                                |
| name        |            | varchar(50)  |                | 名称                                |
| type        |            | varchar(50)  |                | 类型                                |
| value       |            | varchar(200) |                | 值                                  |
| description |            | varchar(100) |                | 描述                                |
| tenant_id   |            | bigint(20)   |                | 租户id                              |
| delete_flag |            | varchar(1)   |                | 删除标记，0未删除，1删除            |
+-------------+------------+--------------+----------------+-------------------------------------+
```

## jsh_sequence 单据编号表

```
+---------------+------------+--------------+-------+----------------+
| COLUMN_NAME   | column_key | column_type  | extra | column_comment |
+---------------+------------+--------------+-------+----------------+
| seq_name      | PRI        | varchar(50)  |       | 序列名称       |
| min_value     |            | bigint(20)   |       | 最小值         |
| max_value     |            | bigint(20)   |       | 最大值         |
| current_val   |            | bigint(20)   |       | 当前值         |
| increment_val |            | int(11)      |       | 增长步数       |
| remark        |            | varchar(500) |       | 备注           |
+---------------+------------+--------------+-------+----------------+
```

## jsh_serial_number 序列号表

```
+---------------+------------+---------------+----------------+-------------------------------------+
| COLUMN_NAME   | column_key | column_type   | extra          | column_comment                      |
+---------------+------------+---------------+----------------+-------------------------------------+
| id            | PRI        | bigint(20)    | auto_increment | 主键                                |
| material_id   |            | bigint(20)    |                | 产品表id                            |
| depot_id      |            | bigint(20)    |                | 仓库id                              |
| serial_number |            | varchar(64)   |                | 序列号                              |
| is_sell       |            | varchar(1)    |                | 是否卖出，0未卖出，1卖出            |
| remark        |            | varchar(1024) |                | 备注                                |
| delete_flag   |            | varchar(1)    |                | 删除标记，0未删除，1删除            |
| create_time   |            | datetime      |                | 创建时间                            |
| creator       |            | bigint(20)    |                | 创建人                              |
| update_time   |            | datetime      |                | 更新时间                            |
| updater       |            | bigint(20)    |                | 更新人                              |
| in_bill_no    |            | varchar(50)   |                | 入库单号                            |
| out_bill_no   |            | varchar(50)   |                | 出库单号                            |
| tenant_id     |            | bigint(20)    |                | 租户id                              |
+---------------+------------+---------------+----------------+-------------------------------------+
```

## jsh_supplier 供应商/客户信息表

```
+----------------+------------+---------------+----------------+-------------------------------------------+
| COLUMN_NAME    | column_key | column_type   | extra          | column_comment                            |
+----------------+------------+---------------+----------------+-------------------------------------------+
| id             | PRI        | bigint(20)    | auto_increment | 主键                                      |
| supplier       |            | varchar(255)  |                | 供应商名称                                |
| contacts       |            | varchar(100)  |                | 联系人                                    |
| phone_num      |            | varchar(30)   |                | 联系电话                                  |
| email          |            | varchar(50)   |                | 电子邮箱                                  |
| description    |            | varchar(500)  |                | 备注                                      |
| isystem        |            | tinyint(4)    |                | 是否系统自带 0==系统 1==非系统            |
| type           |            | varchar(20)   |                | 类型                                      |
| enabled        |            | bit(1)        |                | 启用                                      |
| advance_in     |            | decimal(24,6) |                | 预收款                                    |
| begin_need_get |            | decimal(24,6) |                | 期初应收                                  |
| begin_need_pay |            | decimal(24,6) |                | 期初应付                                  |
| all_need_get   |            | decimal(24,6) |                | 累计应收                                  |
| all_need_pay   |            | decimal(24,6) |                | 累计应付                                  |
| fax            |            | varchar(30)   |                | 传真                                      |
| telephone      |            | varchar(30)   |                | 手机                                      |
| address        |            | varchar(50)   |                | 地址                                      |
| tax_num        |            | varchar(50)   |                | 纳税人识别号                              |
| bank_name      |            | varchar(50)   |                | 开户行                                    |
| account_number |            | varchar(50)   |                | 账号                                      |
| tax_rate       |            | decimal(24,6) |                | 税率                                      |
| tenant_id      |            | bigint(20)    |                | 租户id                                    |
| delete_flag    |            | varchar(1)    |                | 删除标记，0未删除，1删除                  |
+----------------+------------+---------------+----------------+-------------------------------------------+
```

## jsh_system_config 系统参数

```
+-----------------------+------------+--------------+----------------+-------------------------------------------------+
| COLUMN_NAME           | column_key | column_type  | extra          | column_comment                                  |
+-----------------------+------------+--------------+----------------+-------------------------------------------------+
| id                    | PRI        | bigint(20)   | auto_increment | 主键                                            |
| company_name          |            | varchar(50)  |                | 公司名称                                        |
| company_contacts      |            | varchar(20)  |                | 公司联系人                                      |
| company_address       |            | varchar(50)  |                | 公司地址                                        |
| company_tel           |            | varchar(20)  |                | 公司电话                                        |
| company_fax           |            | varchar(20)  |                | 公司传真                                        |
| company_post_code     |            | varchar(20)  |                | 公司邮编                                        |
| sale_agreement        |            | varchar(500) |                | 销售协议                                        |
| depot_flag            |            | varchar(1)   |                | 仓库启用标记，0未启用，1启用                    |
| customer_flag         |            | varchar(1)   |                | 客户启用标记，0未启用，1启用                    |
| minus_stock_flag      |            | varchar(1)   |                | 负库存启用标记，0未启用，1启用                  |
| purchase_by_sale_flag |            | varchar(1)   |                | 以销定购启用标记，0未启用，1启用                |
| tenant_id             |            | bigint(20)   |                | 租户id                                          |
| delete_flag           |            | varchar(1)   |                | 删除标记，0未删除，1删除                        |
+-----------------------+------------+--------------+----------------+-------------------------------------------------+
```

## jsh_tenant 租户

```
+----------------+------------+--------------+----------------+----------------------------------------------+
| COLUMN_NAME    | column_key | column_type  | extra          | column_comment                               |
+----------------+------------+--------------+----------------+----------------------------------------------+
| id             | PRI        | bigint(20)   | auto_increment | 主键                                         |
| tenant_id      |            | bigint(20)   |                | 用户id                                       |
| login_name     |            | varchar(255) |                | 登录名                                       |
| user_num_limit |            | int(11)      |                | 用户数量限制                                 |
| type           |            | varchar(1)   |                | 租户类型，0免费租户，1付费租户               |
| enabled        |            | bit(1)       |                | 启用 0-禁用  1-启用                          |
| create_time    |            | datetime     |                | 创建时间                                     |
| expire_time    |            | datetime     |                | 到期时间                                     |
| remark         |            | varchar(500) |                | 备注                                         |
+----------------+------------+--------------+----------------+----------------------------------------------+
```

## jsh_unit 多单位表

```
+------------------+------------+-------------+----------------+-------------------------------------+
| COLUMN_NAME      | column_key | column_type | extra          | column_comment                      |
+------------------+------------+-------------+----------------+-------------------------------------+
| id               | PRI        | bigint(20)  | auto_increment | 主键                                |
| name             |            | varchar(50) |                | 名称，支持多单位                    |
| basic_unit       |            | varchar(50) |                | 基础单位                            |
| other_unit       |            | varchar(50) |                | 副单位                              |
| other_unit_two   |            | varchar(50) |                | 副单位2                             |
| other_unit_three |            | varchar(50) |                | 副单位3                             |
| ratio            |            | int(11)     |                | 比例                                |
| ratio_two        |            | int(11)     |                | 比例2                               |
| ratio_three      |            | int(11)     |                | 比例3                               |
| tenant_id        |            | bigint(20)  |                | 租户id                              |
| delete_flag      |            | varchar(1)  |                | 删除标记，0未删除，1删除            |
+------------------+------------+-------------+----------------+-------------------------------------+
```

## jsh_user 用户表

```
+-------------+------------+--------------+----------------+--------------------------------------------+
| COLUMN_NAME | column_key | column_type  | extra          | column_comment                             |
+-------------+------------+--------------+----------------+--------------------------------------------+
| id          | PRI        | bigint(20)   | auto_increment | 主键                                       |
| username    |            | varchar(255) |                | 用户姓名--例如张三                         |
| login_name  |            | varchar(255) |                | 登录用户名                                 |
| password    |            | varchar(50)  |                | 登陆密码                                   |
| position    |            | varchar(200) |                | 职位                                       |
| department  |            | varchar(255) |                | 所属部门                                   |
| email       |            | varchar(100) |                | 电子邮箱                                   |
| phonenum    |            | varchar(100) |                | 手机号码                                   |
| ismanager   |            | tinyint(4)   |                | 是否为管理者 0==管理者 1==员工             |
| isystem     |            | tinyint(4)   |                | 是否系统自带数据                           |
| Status      |            | tinyint(4)   |                | 状态，0：正常，1：删除，2封禁              |
| description |            | varchar(500) |                | 用户描述信息                               |
| remark      |            | varchar(500) |                | 备注                                       |
| tenant_id   |            | bigint(20)   |                | 租户id                                     |
+-------------+------------+--------------+----------------+--------------------------------------------+
```

## jsh_user_business 用户/角色/模块关系表

```
+-------------+------------+----------------+----------------+-------------------------------------+
| COLUMN_NAME | column_key | column_type    | extra          | column_comment                      |
+-------------+------------+----------------+----------------+-------------------------------------+
| id          | PRI        | bigint(20)     | auto_increment | 主键                                |
| type        |            | varchar(50)    |                | 类别                                |
| key_id      |            | varchar(50)    |                | 主id                                |
| value       |            | varchar(10000) |                | 值                                  |
| btn_str     |            | varchar(2000)  |                | 按钮权限                            |
| tenant_id   |            | bigint(20)     |                | 租户id                              |
| delete_flag |            | varchar(1)     |                | 删除标记，0未删除，1删除            |
+-------------+------------+----------------+----------------+-------------------------------------+
```

