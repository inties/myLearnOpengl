## 高级Opengl

### 深度测试

opengl中的深度测试默认是在片段着色器执行后进行的，通过深度测试的片段可能会修改深度缓冲中的值，并将自己的值写入颜色缓冲中。没有通过的片段则会被丢弃。

#### 核心概念
##### 深度缓冲

存储每个片段的深度值(z值)，防止被遮挡面渲染到前方

##### 非线性深度

实际深度值按\[1/z\]比例分布，近处精度高远处精度低

##### 提前深度测试

提前深度测试是 GPU 渲染管线中的一部分，通常在以下阶段执行：

1. **顶点着色器（Vertex Shader）** 处理完成后，生成图元（Primitives）。
2. 图元经过光栅化（Rasterization），生成片段（Fragments）。
3. 在片段着色器运行之前，GPU 会检查每个片段的深度值是否可以通过深度测试。如果某个片段被遮挡（即深度测试失败），它会被丢弃，不会进入片段着色器。

​	**注意：**提前深度测试是**针对每个 draw call 的片段独立进行的**，而不是在所有 draw call 的片段着色器执行前一次性完成。每个 draw call 的结果（如深度缓冲区的更新）会影响后续 draw call 的深度测试。



现代 GPU（如 NVIDIA 和 AMD 的显卡）通常会自动启用提前深度测试，只要满足以下条件：

* 深度测试已启用。

* 片段着色器不修改深度值。

* 不使用复杂的渲染路径（如 Alpha 混合或丢弃片段，例如 discard 语句）。



#### 关键函数及参数
```cpp
// 启用深度测试
glEnable(GL_DEPTH_TEST); 

// 清除颜色+深度缓冲
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

// 设置比较运算符（默认GL_LESS）
glDepthFunc(GL_ALWAYS/GL_LESS/GL_LEQUAL等); 

// 控制深度缓冲写入（默认GL_TRUE）
glDepthMask(GL_FALSE); 
```

#### 深度值处理
- 观察空间z值 → 非线性变换 → \[0.0, 1.0\]深度值

- 深度值公式：

- ![image-20250227120528218](E:\myLearnOpengl\日志文档\高级Opengl.assets\image-20250227120528218.png)

- 通过下面公式可以将NDC空间中的z重新变换为观察空间中，物体距离摄像机的真实深度
  $$
  \text{linearDepth} = \frac{2 \cdot near \cdot far}{far + near - z_{ndc} \cdot (far - near)}
  $$

  其中$z_{ndc} = z_{depth} \times 2.0 - 1.0 $

#### 深度冲突(Z-fighting)
##### 原因
- 两个表面过于接近，深度缓冲精度不足

##### 解决方案
1. 物体间保持微小偏移（如：y += 0.001）
2. 适当增大近平面距离（near值不宜过小）
3. 使用32位深度缓冲（替代默认24位）

##### 实践要点
- 渲染循环中必须清除深度缓冲
- 写入深度缓冲时无法使用提前深度测试
- 通过gl_FragCoord.z可获取当前片段深度值
- 地板与物体共面时极易出现深度冲突（需特别注意）

内建gl_FragCoord向量的z值包含了那个特定片段的深度值。









## OpenGL模板测试重点总结



#### 核心概念

1. **模板缓冲**：8位/像素，256种模板值，用于控制片段丢弃/保留

2. **执行顺序**：片段着色器 → 模板测试 → 深度测试

3. **常见应用**：物体轮廓、后视镜特效、阴影体积等

4. 基本流程

   ：

   - 启用模板写入 → 渲染物体更新缓冲 → 禁用写入 → 基于模板值渲染其他物体

#### 关键函数

##### 1. 启用测试

```
cpp复制glEnable(GL_STENCIL_TEST);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); // 每帧清除
```

##### 2. 模板掩码

```
cpp复制glStencilMask(0xFF); // 允许写入（默认）
glStencilMask(0x00); // 禁止写入
```

##### 3. 测试函数

```
cpp
复制
glStencilFunc(GLenum func, GLint ref, GLuint mask);
```

- **func**：测试函数（GL_EQUAL, GL_NOTEQUAL等）
- **ref**：参考值（与模板值比较）
- **mask**：位掩码（0xFF表示所有位参与比较）

##### 4. 缓冲操作

```
cpp
复制
glStencilOp(GLenum sfail, GLenum dpfail, GLenum dppass);
```

- 定义模板测试不同阶段的缓冲更新方式：
  - `sfail`：模板测试失败时的操作
  - `dpfail`：模板通过但深度测试失败
  - `dppass`：两者都通过

上面这两个函数定义了片段能否通过模板测试，以及如何影响模板缓冲



#### 物体轮廓实现步骤

1. 绘制物体时设置模板值为1

```
cpp复制glStencilFunc(GL_ALWAYS, 1, 0xFF);
glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
```

1. 绘制放大版物体（仅绘制轮廓部分）

```
cpp复制glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
glStencilMask(0x00); // 禁用模板写入
glDisable(GL_DEPTH_TEST);
// 使用纯色着色器绘制放大模型
```

#### 重要注意事项

1. 模板测试默认禁用，需手动启用
2. 模板值更新发生在深度测试之前
3. 典型组合用法：
   - `glStencilFunc(GL_EQUAL, 1, 0xFF)` + `glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP)`
4. 常见操作值：
   - GL_REPLACE（替换为参考值）
   - GL_KEEP（保持当前值）
   - GL_INVERT（按位取反）

#### 应用场景示例

```
cpp复制// 绘制正常物体（写入模板）
glStencilMask(0xFF);
glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
DrawObjects();

// 绘制轮廓（只渲染模板值≠1的区域）
glStencilMask(0x00);
glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
glDisable(GL_DEPTH_TEST);
DrawScaledObjects();
```





## 透明混合

### **核心概念**

1. **混合作用**

   - 实现物体透明度（透明/半透明效果）
   - 颜色混合公式： 
   - ![image-20250227123734560](E:\myLearnOpengl\日志文档\高级Opengl.assets\image-20250227123734560.png)

2. **两种实现方式**

   ```
   cpp复制// 方式一：完全透明区域片段丢弃（适合硬边缘）
   if(textureColor.a < 0.1)
       discard;
   
   // 方式二：启用混合（适合半透明效果）
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   ```

3. **关键API**

   ```
   cpp复制// 启用混合
   glEnable(GL_BLEND);
   
   // 设置混合因子（常用组合）
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   
   // 可选：分离RGB和Alpha通道的混合因子
   glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
   
   // 设置混合计算方式（默认为相加）
   glBlendEquation(GL_FUNC_ADD);
   ```

4. **透明纹理处理要点**

   ```
   cpp复制// 加载带alpha通道的纹理
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
   
   // 防止边缘插值问题
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   
   //使用GL_REPEAT在插值采样纹素边缘的时候会出现期望之外的颜色
   ```

------

### **渲染顺序问题**

1. **深度测试冲突**

   - 透明区域仍然写入深度缓冲，可能导致错误遮挡

2. **解决方案**

   ```
   先绘制所有不透明的物体。
   对所有透明的物体排序。
   按顺序绘制所有透明的物体。
   
   
   
   
   cpp复制// 1. 先渲染所有不透明物体
   // 2. 对透明物体按距离排序（从远到近）
   std::map<float, glm::vec3> sorted;
   for(auto& pos : vegetation) {
       float distance = glm::length(camera.Position - pos);
       sorted[distance] = pos; // 自动按键排序
   }
   
   // 3. 反向迭代绘制透明物体
   for(auto it = sorted.rbegin(); it != sorted.rend(); ++it) {
       model = glm::translate(glm::mat4(1.0f), it->second);
       glDrawArrays(...);
   }
   ```

------

### **易错点提醒**

1. 混合与深度测试同时启用时，必须手动管理绘制顺序
2. 全透明物体（如草）建议使用`discard`而非混合
3. 半透明物体不能开启面剔除（GL_CULL_FACE）
4. 混合公式选择错误会导致颜色计算异常

------





***



### 背面剔除

#### 原理

​	以某种顺序定义三角形的顶点：即从正面看时，顶点沿着逆时针的顺序定义。这样，我们可以根据从当前角度观察时，顶点按顺时针还是逆时针排列，判断我们处于三角形的正面还是背面。

即，如果我们发现三角形顶点是顺时针排列时，认为我们处于三角形的背面。反之处于正面。

![img](E:\myLearnOpengl\日志文档\高级Opengl.assets\faceculling_windingorder.png)

#### 注意事项：

​	不是所有物体都应该使用面剔除，一般适合于**封闭的不透明物体**。如果是透明物体，背面是能够被看到的；如果是非封闭的物体，例如一张纸，一个平面。如果启用背面剔除，则当我们绕到背后时，此时三角形顶点按逆时针排列，因此这张纸不会被渲染。对于封闭物体来说，例如一个箱子，如果启用了背面剔除，我们飞入箱子内部，发现不会被渲染，也是同样的道理。





#### 如何使用面剔除：





***





### 帧缓冲

#### 基本概念：

​	帧缓冲是用于离屏渲染的容器，可以包含多个附件，比如颜色、深度和模板缓冲。把它比作画布，附件就是画布上的不同图层。

**离屏渲染：**

​	渲染到一个不同的帧缓冲被叫做离屏渲染。`glBindFramebuffer(GL_FRAMEBUFFER, fbo);`绑定后，之后所有的渲染操作将会渲染到当前绑定帧缓冲的附件中，而不是默认帧缓冲中。要保证所有的渲染操作在主窗口中有视觉效果，我们需要再次激活默认帧缓冲，将它绑定到`0`。`glBindFramebuffer(GL_FRAMEBUFFER, 0);`



如何实现离屏渲染：

* 正确创建帧缓冲区
* 渲染结果保存到自定义帧缓冲区
* 启用默认帧缓冲区，从自定义帧缓冲区中采样纹理附件，绘制到屏幕上



实现细节：

* 创建纹理附件和渲染缓冲附件。两者区别为：

* 一般纹理作为颜色附件、RBO作为深度模板附件

  



创建帧缓冲区：

```
// 1. 创建/删除帧缓冲
glGenFramebuffers(1, &fbo);  
glDeleteFramebuffers(1, &fbo);

// 2. 绑定帧缓冲
glBindFramebuffer(GL_FRAMEBUFFER, fbo); 

//3.添加纹理附件
// 创建空纹理
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

// 设置过滤参数
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

// 附加纹理到颜色附件
glFramebufferTexture2D(
  GL_FRAMEBUFFER, 
  GL_COLOR_ATTACHMENT0, 
  GL_TEXTURE_2D, 
  texture, 
  0
);



// 4. 附加渲染缓冲到深度/模板附件

// 创建RBO并分配内存
glGenRenderbuffers(1, &rbo);
glBindRenderbuffer(GL_RENDERBUFFER, rbo);
glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);


glFramebufferRenderbuffer(
  GL_FRAMEBUFFER, 
  GL_DEPTH_STENCIL_ATTACHMENT,
  GL_RENDERBUFFER, 
  rbo
);


// 5. 检查完整性
if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    // 错误处理...

// 6. 切换回默认缓冲
glBindFramebuffer(GL_FRAMEBUFFER, 0);

```



先渲染到FBO，再采样纹理，渲染到屏幕

```

// 第一遍：渲染到FBO
glBindFramebuffer(GL_FRAMEBUFFER, fbo);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
RenderScene();

// 第二遍：渲染到屏幕
glBindFramebuffer(GL_FRAMEBUFFER, 0);
glDisable(GL_DEPTH_TEST); // 禁用深度测试
screenShader.use();
glBindTexture(GL_TEXTURE_2D, texture);
RenderQuad();

```





***

### 立方体贴图

这一节引入了一种新的纹理类型——立方体贴图。本质上是由6副2D的纹理组成的立方体，允许通过方向向量采样。

天空盒和环境光贴图是两种典型应用：

让场景中的物体采样天空盒，可以得到镜面和玻璃材质。

环境光贴图也通常是立方体贴图（Cubemap），但它不仅仅用来表示背景，而是专门用于描述场景中的光照环境。它可以是预计算的（**如基于图像的光照，IBL**）或动态生成的（如**实时反射探针**）。





天空盒，是一个带有立方体贴图的1×1×1的盒子。通过使用特殊的view矩阵，在视图空间中这个盒子始终位于摄像机的四周，与摄像机的相对位置不变。让观察者产生盒子上绘制的内容距自己很远的错觉。









***



### 高级数据

这一节介绍了一些操作GPU中的缓冲数据的方法

* 
* 插入或者更新缓冲内存的某一部分







##### 插入或者更新缓冲内存的某一部分：

- `glBufferSubData(target, offset, size, data)`
- 允许填充缓冲的特定区域（需先分配内存）
- 示例：`glBufferSubData(GL_ARRAY_BUFFER, 24, sizeof(data), &data`



##### 请求缓冲内存的指针，直接将数据复制到缓冲当中

也可以称为内存映射

- 通过 `glMapBuffer(target, access)` 获取内存指针直接操作

- 操作流程：

  ```
  void* ptr = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
  memcpy(ptr, data, sizeof(data));
  glUnmapBuffer(GL_ARRAY_BUFFER);//不再需要该指针
  ```



##### 复制缓冲到另一个缓冲中

- 专用复制目标

  - `GL_COPY_READ_BUFFER`：复制源
  - `GL_COPY_WRITE_BUFFER`：复制目标

- 典型使用场景：

  ```
  glBindBuffer(GL_COPY_READ_BUFFER, vbo1);
  glBindBuffer(GL_COPY_WRITE_BUFFER, vbo2);
  glCopyBufferSubData(readTarget, writeTarget, readOffset, writeOffset, size);
  ```



##### 分批顶点属性

顶点缓冲中的顶点数据排列方式：

* 交错排列，将每一个顶点的位置、法线和/或纹理坐标紧密放置在一起。推荐使用交错方法，因为这样一来，每个顶点着色器运行时所需要的顶点属性在内存中会更加紧密对齐。
* 分批排列，将每一种属性类型的向量数据打包(Batch)为一个大的区块，而不是对它们进行交错储存。由于通过读取文件拿到的数据一般是分批的，输入缓冲会比较方便。

分批排列加载数据例子：

```
float positions[] = { ... };
float normals[] = { ... };
float tex[] = { ... };
// 填充缓冲
glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(positions), &positions);
glBufferSubData(GL_ARRAY_BUFFER, sizeof(positions), sizeof(normals), &normals);
glBufferSubData(GL_ARRAY_BUFFER, sizeof(positions) + sizeof(normals), sizeof(tex), &tex);
```

更改VAO：
```
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);  
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(sizeof(positions)));  
glVertexAttribPointer(
  2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(sizeof(positions) + sizeof(normals)));

```





****

### 高级GLSL

#### 内置变量

##### gl_FragCoord

`gl_FragCoord` 是 OpenGL 片段着色器中的一个内置变量，提供了当前片段的屏幕坐标和深度值。它在实现屏幕空间效果、深度相关计算以及窗口尺寸无关的渲染中非常有用。





##### gl_Position和gl_PointSize

我们能够选用的其中一个图元是GL_POINTS，如果使用它的话，每一个顶点都是一个图元，都会被渲染为一个点。我们可以通过OpenGL的**glPointSize**函数来设置渲染出来的点的大小，但我们也可以在顶点着色器中修改这个值。

你会看到每个顶点被渲染为一个点，且大小由 gl_PointSize 控制（比如**你设为 10.0，点就会变成 10 像素大小**）

```
glEnable(GL_PROGRAM_POINT_SIZE);//修改点大小的功能默认是禁用的，需要启用
void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);    
    gl_PointSize = gl_Position.z;    
}
```





##### gl_VertexID

##### gl_FragDepth

这个变量允许在片段着色器中更改片段的深度z，注意这会使得OpengL禁用提前深度测试

可以通过这条命令来允许部分提前深度测试

layout (depth_<condition>) out float gl_FragDepth;

| 条件        | 描述                                                         |
| :---------- | :----------------------------------------------------------- |
| `any`       | 默认值。提前深度测试是禁用的，你会损失很多性能               |
| `greater`   | 你只能让深度值比`gl_FragCoord.z`更大                         |
| `less`      | 你只能让深度值比`gl_FragCoord.z`更小                         |
| `unchanged` | 如果你要写入`gl_FragDepth`，你将只能写入`gl_FragCoord.z`的值 |



#### 接口块

自定义结构体，用于顶点和片段着色器之间的数据传递。

```
out VS_OUT
{
    vec2 TexCoords;
} vs_out;

in VS_OUT
{
    vec2 TexCoords;//结构体内部的名称可以是随机的
} fs_in;

 FragColor = texture(texture, fs_in.TexCoords);   
```



#### UBO

将着色器需要的uniform数据批量存入缓冲中，成为uniform buffer object，多个着色器可能需要相同的uniform变量，这时可以获取UBO



##### UBO的布局

默认是share布局，但std140更加高效。它依照一定的规则，可以显示地计算每个变量的偏移量，规则如下：

| 类型                | 布局规则                                                     |
| :------------------ | :----------------------------------------------------------- |
| 标量，比如int和bool | 每个标量的基准对齐量为N。（N为4字节）                        |
| 向量                | 2N或者4N。这意味着vec3的基准对齐量为4N。                     |
| 标量或向量的数组    | 每个元素的基准对齐量与vec4的相同。                           |
| 矩阵                | 储存为列向量的数组，每个向量的基准对齐量与vec4的相同。       |
| 结构体              | 等于所有元素根据规则计算后的大小，但会填充到vec4大小的倍数。 |

```
layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
};
```



##### UBO的使用

![img](E:\myLearnOpengl\日志文档\高级Opengl.assets\advanced_glsl_binding_points.png)

* 将顶点着色器的Uniform块设置为某个绑定点。
* 创建UBO，通过glBufferData分配内存资源，将UBO绑定到某个绑定点上，可以使用glBindBuffer(GL_UNIFORM_BUFFER, 0);或者glBindBufferRange(GL_UNIFORM_BUFFER, 0, uboMatrices, 0, 2 * sizeof(glm::mat4));
* 为UBO填充数据，可以使用glBufferSubData。某些数据可以在渲染循环内填充







***

### 实例化

在这一章中，成功通过实例化渲染，渲染了大量物体的同时，保证了渲染的效率。

​	实例化这项技术能够让我们使用**一个渲染调用**来绘制**同一物体的多个实例**，来节省每次绘制物体时**CPU -> GPU的通信**，它只需要一次即可。如果想使用实例化渲染，我们只需要将glDrawArrays和glDrawElements的渲染调用分别改为**glDrawArraysInstanced**和**glDrawElementsInstanced**就可以了。

#### 实例化的drawcall



#### 数据传入

​	由于实例化使用一次drawcall绘制所有实例，我们需要**一次性传入**所有实例需要的数据



##### 通过uniform变量数组传入





##### 通过顶点属性传入

​	和一般的流程一样，暂存到VBO中，然后通过VAO指定着色器中的数据布局，将数据传入着色器。不同的是，一般的VAO是为以一个顶点的数据为一组向着色器传入数据；而在实例化渲染中，**是每个实例为一组**，向着色器传入数据。通过`glVertexAttribDivisor(n, 1)`说明序号为n的顶点属性是以一个实例为一组传入着色器的。

```
glEnableVertexAttribArray(3); 
glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);
glVertexAttribDivisor(3, 1);//glVertexAttribDivisor(n, 1) 表示该顶点属性的数据是按实例（per-instance）更新的，而不是按顶点（per-vertex）
```





​	顶点属性最大只能占4个字节，因此下面的声明实际上隐式地占据了3、4、5、6号位置（每个列向量占据一个位置）

```
layout (location = 3) in mat4 instanceMatrix;
```







#### 注意事项

**只能针对单一的顶点数据集合（一个 VAO）进行实例化绘制**。

```
for (unsigned int i = 0; i < rock.meshes.size(); i++)
{
    glBindVertexArray(rock.meshes[i].VAO);
    glDrawElementsInstanced(GL_TRIANGLES, static_cast<unsigned int>(rock.meshes[i].indices.size()), GL_UNSIGNED_INT, 0, amount);
    glBindVertexArray(0);
}
```

​	rock 是一个复杂的模型，由多个网格（meshes）组成，每个网格有独立的顶点数据和索引数据（分别绑定在不同的 VAO 中）。这就导致了一个问题：**一个 glDrawElementsInstanced 调用无法同时处理多个不同的网格**。



| 特性             | `glDrawElements`                         | `glDrawArrays`                               |
| ---------------- | ---------------------------------------- | -------------------------------------------- |
| **顶点索引方式** | 使用索引数组间接引用顶点数据             | 直接按顺序使用顶点数组中的数据               |
| **内存效率**     | 更高效，支持顶点复用，减少重复顶点数据   | 不支持顶点复用，可能需要重复存储相同顶点数据 |
| **灵活性**       | 更灵活，适合复杂模型（如共享顶点的网格） | 简单直接，适合简单几何形状                   |
| **参数复杂度**   | 需要额外的索引数组和索引类型参数         | 参数更少，使用更简单                         |
| **适用场景**     | 复杂模型（如网格、地形、模型加载）       | 简单几何体（如矩形、立方体、点云）           |
