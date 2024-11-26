
- 对于`["女孩","天空",...]`等词语级别的提示语，将其嵌入到序列长度为$l$、维度为$d$的空间中，形成嵌入张量$P_{voc}\in\mathbb{R}^{1\times l\times d}$。
- 对于`["坐在树枝上戴着帽子的小孩",...]`等句子级别的提示语，将其嵌入到Token数量为$n$、序列长度为$l$、维度为$d$的空间中，形成嵌入张量$P_{sen}\in\mathbb{R}^{n\times l\times d}$。
为了减少计算量和内存占用，将$\{P_{voc},P_{sen}\}$中的序列长度$l$维度取平均值，从而降低到$\{\overline{P}_{voc},\overline{P}_{sen}\}\in\mathbb{R}^{n\times d}$。这样做虽然会损失很多细粒度信息，但是实验证明不会对性能造成太多的影响。

### 区域句子对齐
给定物体嵌入张量$\hat{O}$和提示词嵌入$\{\overline{P}_{voc},\overline{P}_{sen}\}$，定义对齐得分为$S=\hat{O}\cdot(\overline{P}_{voc},\overline{P}_{sen})^T\in\mathbb{R}^{n\times m}$。

### 事物相等化对齐
给定$q$个查询，$c$个目标查询类别，预测分数$S\in\mathbb{R}^{q\times c}$和掩码$M\in\mathbb{R}^{q\times h\times w}$，得到最终的语义掩码$\hat{M}=\sum_{\textcolor{red}{i}=1}^{q}S_{\textcolor{red}{i},c}M_{\textcolor{red}{i},h,w}\in\mathbb{R}^{c\times h\times w}$。

### 单阶段多数据训练
损失函数为$\mathcal{L}=\overbrace{\mathcal{L}_{\text{class}}+\mathcal{L}_{\text{bbox}}+\mathcal{L}_{\text{giou}}}^{\text{Encoder和Decoder}}+\overbrace{\mathcal{L}_{\text{mask}}+\mathcal{L}_{\text{dice}}}^{最后一层\text{Decoder}}$。其中：
1. $\mathcal{L}_{\text{class}}$（Focal Loss）：为Encoder区分前景和背景、为Decoder对齐语言和视觉嵌入张量。
2. $\mathcal{L}_{\text{bbox}}$：画框回归的L1范数，作用于Encoder和Decoder。
3. $\mathcal{L}_{\text{giou}}$：画框回归的GIoU损失，作用于Encoder和Decoder。
4. $\mathcal{L}_{\text{mask}}$：掩码分割的交叉熵损失，作用于最后一层Decoder。
5. $\mathcal{L}_{\text{dice}}$：掩码分割的Dice损失，作用于最后一层Decoder。
