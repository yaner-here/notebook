令$\mathbf{M}^{(i)}$（Memory）表示第`i`层Decoder的输出。特殊地，$\mathbf{M}^{(0)}$表示最后一层Encoder的输出。

$$
\text{DETR}: \begin{cases}
	\mathbf{K}^{(i)} = \mathbf{X} + \mathbf{E}_{\text{pos}} \\ 
	\mathbf{V}^{(i)} = \mathbf{X} \\
	\mathbf{Q}^{(i)} = \mathbf{M}^{(i-1)} + \mathbf{Q}_{\text{obj}} \\
	\mathbf{M}^{(i)} = \text{TransformerEncoder}(\mathbf{K}^{(i)}, \mathbf{V}^{(i)}, \mathbf{Q}^{(i)}) \\
\end{cases}
$$

$$
\text{Conditional DETR}: \begin{cases}
	\mathbf{K}^{(i)} = \mathbf{X} \oplus \mathbf{E}_{\text{pos}} \\ 
	\mathbf{V}^{(i)} = \mathbf{X} \\
	\mathbf{Q}^{(i)} = \mathbf{M}^{(i-1)} \oplus (\mathbf{M}^{(i-1)} \cdot \sigma(\mathbf{Q}_{\text{obj}})) \\
	\mathbf{M}^{(i)} = \text{TransformerEncoder}(\mathbf{K}^{(i)}, \mathbf{V}^{(i)}, \mathbf{Q}^{(i)}) \\
\end{cases}
$$

DETR的每个Encoder层有三部分：一是自注意力层，用于消除重复预测，该层在从前一解码器层输出的嵌入之间进行交互，这些嵌入用于类别和边界框预测；二是交叉注意力层，该层聚合从编码器输出的嵌入，以细化解码器嵌入，从而提高类别和边界框预测的精度；三是前馈层。


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

DINO的创新性：

 1. 对比学习去噪。原先的目标框都是正样本，对应着某个存在的类别。DINO引入额外的随机框，令其对应“不存在”的类别，作为负样本。
 2. 混合查询。DINO的措施类似于DEformer-DETR
 3. 梯度回传两层（Look Forward Twice）。Decoder原先是由若干个Decoder层串行连接。现在每个Decoder层的输出由这一层和前一层的输出共同计算得到。
 4. 取消了二分图匹配。