# 回调函数模块说明

## 一、目录结构

```
callbacks/
├── JammerCallbacks.h          # Jammer 对象回调函数声明
├── JammerCallbacks.cpp        # Jammer 对象回调函数实现
├── PassiveJammerCallbacks.h   # PassiveJammer 对象回调函数声明
├── PassiveJammerCallbacks.cpp # PassiveJammer 对象回调函数实现
└── README.md                  # 本说明文档
```

## 二、设计目的

将不同对象的回调函数分离到独立的文件中，避免 `VRLinkManager.cpp` 变得过于庞大和难以维护。

### 2.1 优势

- ✅ **代码组织清晰**：每个对象类型的回调函数在独立的文件中
- ✅ **易于维护**：修改某个对象的回调不影响其他对象
- ✅ **易于扩展**：添加新对象类型时，只需创建新的回调文件
- ✅ **减少冲突**：多人协作时，不同对象的回调不会产生代码冲突

### 2.2 文件命名规范

- 头文件：`{ObjectType}Callbacks.h`
- 实现文件：`{ObjectType}Callbacks.cpp`
- 例如：`JammerCallbacks.h`、`PassiveJammerCallbacks.cpp`

## 三、回调函数结构

### 3.1 每个对象类型包含三个回调函数

1. **对象添加回调**：`on{ObjectType}Added()`
   - 当对象被发现时触发
   - 为新对象注册更新回调
   - 通知 Java 层：`{ObjectType}_DISCOVER`

2. **对象更新回调**：`on{ObjectType}Updated()`
   - 当对象属性更新时触发
   - 通知 Java 层：`{ObjectType}_UPDATE`

3. **对象移除回调**：`on{ObjectType}Removed()`
   - 当对象被删除时触发
   - 通知 Java 层：`{ObjectType}_REMOVED`

### 3.2 回调函数实现模式

```cpp
// 头文件：{ObjectType}Callbacks.h
#pragma once
#include "{objectType}/CtRef{ObjectType}.h"

void on{ObjectType}Added(CtRef{ObjectType}* obj, void* userData);
void on{ObjectType}Updated(CtRef{ObjectType}* obj, void* userData);
void on{ObjectType}Removed(CtRef{ObjectType}* obj, void* userData);
```

```cpp
// 实现文件：{ObjectType}Callbacks.cpp
#include "{ObjectType}Callbacks.h"
#include "EventBridge.h"
#include "{objectType}/Ct{ObjectType}StateRepository.h"
#include <sstream>

// 前向声明更新回调
void on{ObjectType}Updated(CtRef{ObjectType}* obj, void* userData);

// 实现三个回调函数...
```

## 四、添加新对象类型的步骤

### 4.1 创建回调文件

1. **创建头文件**：`callbacks/{ObjectType}Callbacks.h`
   ```cpp
   #pragma once
   #include "{objectType}/CtRef{ObjectType}.h"
   
   void on{ObjectType}Added(CtRef{ObjectType}* obj, void* userData);
   void on{ObjectType}Updated(CtRef{ObjectType}* obj, void* userData);
   void on{ObjectType}Removed(CtRef{ObjectType}* obj, void* userData);
   ```

2. **创建实现文件**：`callbacks/{ObjectType}Callbacks.cpp`
   - 实现三个回调函数
   - 参考 `JammerCallbacks.cpp` 的实现模式

### 4.2 在 VRLinkManager.cpp 中集成

1. **包含头文件**：
   ```cpp
   #include "callbacks/{ObjectType}Callbacks.h"
   ```

2. **添加全局列表**：
   ```cpp
   static std::unique_ptr<CtRef{ObjectType}List> g_{objectType}List;
   ```

3. **在 init() 中初始化**：
   ```cpp
   // 设置 StateRepository 创建函数
   CtRef{ObjectType}::setStateRepCreator(Ct{ObjectType}StateRepository::create);
   
   // 创建对象列表
   g_{objectType}List.reset(new CtRef{ObjectType}List(_conn.get()));
   
   // 注册回调
   g_{objectType}List->add{ObjectType}AdditionCallback(on{ObjectType}Added, nullptr);
   g_{objectType}List->add{ObjectType}RemovalCallback(on{ObjectType}Removed, nullptr);
   
   // 为已存在的对象注册更新回调
   CtRef{ObjectType}* obj = g_{objectType}List->first();
   while (obj) {
       obj->addPostUpdateCallback(on{ObjectType}Updated, nullptr);
       obj = obj->next();
   }
   ```

4. **在 shutdown() 中清理**：
   ```cpp
   g_{objectType}List.reset();
   ```

## 五、当前支持的对象类型

| 对象类型 | 头文件 | 实现文件 | 事件类型 |
|---------|--------|---------|---------|
| **IJammer** | `JammerCallbacks.h` | `JammerCallbacks.cpp` | `IJammer_DISCOVER`<br>`IJammer_UPDATE`<br>`IJammer_REMOVED` |
| **IPassiveJammer** | `PassiveJammerCallbacks.h` | `PassiveJammerCallbacks.cpp` | `IPassiveJammer_DISCOVER`<br>`IPassiveJammer_UPDATE`<br>`IPassiveJammer_REMOVED` |

## 六、注意事项

### 6.1 前向声明

在实现文件中，如果添加回调需要调用更新回调，需要前向声明：

```cpp
// 前向声明更新回调
void on{ObjectType}Updated(CtRef{ObjectType}* obj, void* userData);

// 添加回调中使用
void on{ObjectType}Added(...) {
    obj->addPostUpdateCallback(on{ObjectType}Updated, nullptr);
    // ...
}
```

### 6.2 EventBridge 访问

所有回调函数都通过 `EventBridge::get()` 获取 Java 回调函数：

```cpp
JavaEventCallback cb = EventBridge::get();
if (cb) {
    // 构造 JSON 数据
    // 调用 cb(...)
}
```

### 6.3 JSON 数据格式

回调函数需要构造 JSON 格式的数据传递给 Java 层。建议：
- 使用 `std::ostringstream` 构造 JSON
- 确保 JSON 格式正确（转义特殊字符）
- 可选字段只在非空时包含

## 七、示例：添加新对象类型

假设要添加 `ZHRadar` 对象的支持：

### 步骤1：创建回调文件

**`callbacks/ZHRadarCallbacks.h`：**
```cpp
#pragma once
#include "zhradar/CtRefZHRadar.h"

void onZHRadarAdded(CtRefZHRadar* obj, void* userData);
void onZHRadarUpdated(CtRefZHRadar* obj, void* userData);
void onZHRadarRemoved(CtRefZHRadar* obj, void* userData);
```

**`callbacks/ZHRadarCallbacks.cpp`：**
```cpp
#include "ZHRadarCallbacks.h"
#include "EventBridge.h"
#include "zhradar/CtZHRadarStateRepository.h"
#include <sstream>

void onZHRadarUpdated(CtRefZHRadar* obj, void* userData);

void onZHRadarAdded(CtRefZHRadar* obj, void* userData) {
    if (!obj) return;
    obj->addPostUpdateCallback(onZHRadarUpdated, nullptr);
    
    JavaEventCallback cb = EventBridge::get();
    if (cb) {
        CtZHRadarStateRepository* rep = obj->ZHRadarStateRepository();
        if (!rep) return;
        
        std::ostringstream ss;
        ss << "{\"radarId\":\"" << rep->radarId() << "\",...}";
        cb("OBJECT", "ZHRadar_DISCOVER", "RemoteFederate",
           rep->radarId().c_str(), ss.str().c_str());
    }
}

// ... 实现其他回调函数
```

### 步骤2：在 VRLinkManager.cpp 中集成

```cpp
// 包含头文件
#include "callbacks/ZHRadarCallbacks.h"

// 添加全局列表
static std::unique_ptr<CtRefZHRadarList> g_radarList;

// 在 init() 中初始化
g_radarList.reset(new CtRefZHRadarList(_conn.get()));
g_radarList->addZHRadarAdditionCallback(onZHRadarAdded, nullptr);
// ...
```

## 八、总结

通过将回调函数分离到独立的文件中，代码结构更加清晰，易于维护和扩展。添加新对象类型时，只需：

1. 创建回调文件（.h 和 .cpp）
2. 在 VRLinkManager.cpp 中包含头文件
3. 在 init() 中初始化
4. 在 shutdown() 中清理

这样可以让 `VRLinkManager.cpp` 保持简洁，专注于对象列表的管理和初始化逻辑。

