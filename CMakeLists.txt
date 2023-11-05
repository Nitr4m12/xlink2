project(xlink2 CXX ASM)

add_library(xlink2 OBJECT
  include/xlink2/xlink2.h
  include/xlink2/xlink2ActionTriggerCtrl.h
  include/xlink2/xlink2AlwaysTriggerCtrl.h
  include/xlink2/xlink2ArrangeGroupParam.h
  include/xlink2/xlink2AssetExecutor.h
  include/xlink2/xlink2AssetExecutorELink.h
  include/xlink2/xlink2AssetExecutorSLink.h
  include/xlink2/xlink2BlendContainer.h
  include/xlink2/xlink2BoneMtx.h
  include/xlink2/xlink2ContainerBase.h
  include/xlink2/xlink2ContainerType.h
  include/xlink2/xlink2ErrorMgr.h
  include/xlink2/xlink2Event.h
  include/xlink2/xlink2IEventCallbackELink.h
  include/xlink2/xlink2IEventCallbackSLink.h
  include/xlink2/xlink2ILockProxy.h
  include/xlink2/xlink2Locator.h
  include/xlink2/xlink2LockProxy.h
  include/xlink2/xlink2ModelAssetConnection.h
  include/xlink2/xlink2OuterLockProxy.h
  include/xlink2/xlink2PropertyTriggerCtrl.h
  include/xlink2/xlink2ResEset.h
  include/xlink2/xlink2ResourceAccessor.h
  include/xlink2/xlink2ResourceAccessorELink.h
  include/xlink2/xlink2ResourceAccessorSLink.h
  include/xlink2/xlink2ResourceBuffer.h
  include/xlink2/xlink2ResourceParamCreator.h
  include/xlink2/xlink2ResourceUtil.h
  include/xlink2/xlink2ResTriggerOverwriteParam.h
  include/xlink2/xlink2ResUserInfo.h
  include/xlink2/xlink2SwitchContainer.h
  include/xlink2/xlink2System.h
  include/xlink2/xlink2SystemELink.h
  include/xlink2/xlink2SystemSLink.h
  include/xlink2/xlink2TriggerCtrl.h
  include/xlink2/xlink2TriggerCtrlMgr.h
  include/xlink2/xlink2TriggerLocator.h
  include/xlink2/xlink2TriggerType.h
  include/xlink2/xlink2Util.h
  include/xlink2/xlink2User.h
  include/xlink2/xlink2UserInstance.h
  include/xlink2/xlink2UserInstanceELink.h
  include/xlink2/xlink2UserInstanceSLink.h
  include/xlink2/xlink2UserResource.h
  include/xlink2/xlink2UserResourceELink.h
  include/xlink2/xlink2UserResourceSLink.h
  src/xlink2ActionTriggerCtrl.cpp
  src/xlink2AlwaysTriggerCtrl.cpp
  src/xlink2AssetExecutor.cpp
  src/xlink2AssetExecutorELink.cpp
  src/xlink2AssetExecutorSLink.cpp
  src/xlink2BlendContainer.cpp
  src/xlink2ContainerBase.cpp
  src/xlink2ErrorMgr.cpp
  src/xlink2Event.cpp
  src/xlink2IEventCallbackELink.cpp
  src/xlink2IEventCallbackSLink.cpp
  src/xlink2ILockProxy.cpp
  src/xlink2Locator.cpp
  src/xlink2LockProxy.cpp
  src/xlink2ModelAssetConnection.cpp
  src/xlink2OuterLockProxy.cpp
  src/xlink2ParamDefineTable.cpp
  src/xlink2PropertyTriggerCtrl.cpp
  src/xlink2ResourceAccessor.cpp
  src/xlink2ResourceAccessorELink.cpp
  src/xlink2ResourceAccessorSLink.cpp
  src/xlink2ResourceBuffer.cpp
  src/xlink2ResourceParamCreator.cpp
  src/xlink2ResourceUtil.cpp
  src/xlink2SwitchContainer.cpp
  src/xlink2System.cpp
  src/xlink2SystemELink.cpp
  src/xlink2SystemSLink.cpp
  src/xlink2TriggerCtrl.cpp
  src/xlink2TriggerCtrlMgr.cpp
  src/xlink2TriggerLocator.cpp
  src/xlink2Util.cpp
  src/xlink2User.cpp
  src/xlink2UserInstance.cpp
  src/xlink2UserInstanceELink.cpp
  src/xlink2UserInstanceSLink.cpp
  src/xlink2UserResource.cpp
  src/xlink2UserResourceELink.cpp
  src/xlink2UserResourceSLink.cpp
)

target_compile_options(xlink2 PRIVATE -fno-exceptions)
target_compile_options(xlink2 PRIVATE -fno-strict-aliasing)
target_compile_options(xlink2 PRIVATE -Wall -Wextra)
target_compile_options(xlink2 PRIVATE -Wno-invalid-offsetof)
target_include_directories(xlink2 PUBLIC include/)

if(NOT TARGET sead)
  find_package(sead)
endif()
target_link_libraries(xlink2 PUBLIC sead)
