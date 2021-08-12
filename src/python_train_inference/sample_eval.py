import pixellib
from pixellib.custom_train import instance_custom_training

train_maskrcnn = instance_custom_training()
train_maskrcnn.modelConfig(network_backbone = "resnet50", num_classes= 1)
train_maskrcnn.load_dataset("/home/deploy/app/tests/database/CholecSeg8k_Mine/Final")
train_maskrcnn.evaluate_model("mask_rcnn_models_gallbladder")
