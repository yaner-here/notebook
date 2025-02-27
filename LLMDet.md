# LLMDet

[LLMDet: Learning Strong Open-Vocabulary Object Detectors under the Supervision of Large Language Models.](https://arxiv.org/abs/2501.18954) 中山大学&阿里巴巴. 2025.01.

![](https://arxiv.org/html/2501.18954v1/x3.png)

在传统OVD框架的基础上，引出DETR Encoder的输出和DETR Decoder使用的Object Query，经过Projector后送入VLLM，期望VLLM的输出文本序列能与描述文本一致，计算Language Modeling Loss。

1. 改Language Modeling Loss
2. 右下方的Prompt Template可以接入检索图像的提示，使得VLLM的输入同时有文本Token和图像Token，图像Token由图中的Encoder输出（也就是Feature Map）接一个Projector而来（反正ViT的Token是连续的，不像文本Token那样离散），检索可以离线/在线检索RAG
3. 洗数据集

# VMCNet

[Modulating CNN Features with Pre-Trained ViT Representations for Open-Vocabulary Object Detection.](https://arxiv.org/abs/2501.16981) 电科大. 2025.01

![](https://arxiv.org/html/2501.16981v1/extracted/6161705/pic_material/main_arch.png)

针对OVD需要模态融合的特点，设计的新型图像Backbone，同时提取ViT和CNN的图像特征。使用[CLIPSelf](https://arxiv.org/abs/2310.01403)框架为基座进行测试。

# 

[Zero-Shot Open-Vocabulary OOD Object Detection and Grounding using Vision Language Models.](https://openreview.net/forum?id=Q2wVVeOpz8#discussion) 慕尼黑工业大学. 

# DynamicEarth

DynamicEarth: How Far are We from Open-Vocabulary Change Detection? 武汉大学. 2025.01

![]()
