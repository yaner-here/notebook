DETR：

$$
\text{DETR}: \begin{cases}
	\mathbf{Q}^{(0)} = 内容查询\mathbf{Q}_{\text{content}} \oplus 位置查询\mathbf{Q}_{\text{position}} \\
	\mathbf{Q}^{(i+1)} = \text{TransformerEncoder}(\mathbf{Q}^{(i)}) \\
	\mathbf{Q}^{\text{final}} = \mathbf{Q}^{(N_{\text{encoder\_layer}})}
\end{cases}
$$

$$
\text{DINO}: \begin{cases}
	\mathbf{Q}^{(0)} = 
\end{cases}
$$


1. DETR对全局做Attention，搜索困难。
2. DETR的Query没有实际含义。DETR创建$N_{\text{query}}$个Query，查询得到$N_{\text{query}}$个框特征向量，克隆两份，分别送进分类头和回归头，用于预测框代表的物体种类、框的`(x, y, h, w)`四个表示位置的自由度。DINO创建$2\times N_{\text{query}}$个Query，分别表示预测

DETR收敛速度慢的两个原因：

1. 全局搜索速度慢。初始时生成$N_{\text{query}}$个框，框的位置均随机。在训练过程中，预测框的位置要逐渐收敛到目标框，该过程耗时较长。
2. 二分图匹配不稳定。训练一个Epoch后，对于同一张图片，目标框保持不变，然而$N_{\text{query}}$个预测框的位置会改变，导致二分图匹配关系发生改变，造成Loss抖动。

DINO的优点：
 1. 取消了二分图匹配。