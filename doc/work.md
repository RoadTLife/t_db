# 20241030
* 尝试实现服务启动的部分

# 20241031
* 查看第三方依赖的引入方式，但是没在第三方依赖中进行 git submooudle update --init 操作导致文件错误

# 20241104
* 添加head相关依赖，学习了std的方式方法，通过添加一个head文件，using::xx 从而减少依赖引入
* 添加Log的形式，方便后续的日志打印
* 服务还未启动成功（TODO 需要推进）
* 上述方式，导致的新的编译错误: 
CMake Error: install(EXPORT "protobuf-targets" ...) includes target "libprotoc" which requires target "absl_time" that is not in any export set.
CMake Error: install(EXPORT "protobuf-targets" ...) includes target "libprotoc" which requires target "absl_type_traits" that is not in any export set.

# 20241105