//
//  ViewController.m
//  CoreAnimationTest
//
//  Created by ishang on 14/11/17.
//  Copyright (c) 2014年 commondec. All rights reserved.
//

#import "ViewController.h"
#import "CoreAnimations.h"
@interface ViewController () {
    UIView * demoView;
    BOOL flag;
}

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    demoView = [[UIView alloc] initWithFrame:CGRectMake(100, 100, 100, 100)];
    [demoView setBackgroundColor:[UIColor redColor]];
    [self.view addSubview:demoView];
    //[demoView.layer addAnimation:[CoreAnimations opacityForever_Animation:1.0] forKey:nil];
    
    UIButton * paulse = [[UIButton alloc] initWithFrame:CGRectMake(10, 10, 30, 40)];
    [paulse setBackgroundColor:[UIColor blackColor]];
    [paulse addTarget:self action:@selector(Pualse) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:paulse];
    
//    UIButton * paulse = [UIButton buttonWithType:UIButtonTypeContactAdd];
//    [paulse addTarget:self action:@selector(Pualse) forControlEvents:UIControlEventTouchUpInside];
//    CABasicAnimation其实可以看作一种特殊的关键帧动画,只有头尾两个关键帧.CAKeyframeAnimation则可以支持任意多个关键帧,关键帧有两种方式来指定,使用path或者使用values,path是一个CGPathRef的值,且path只能对CALayer的 anchorPoint 和 position 属性起作用,且设置了path之后values就不再起效了.而values则更加灵活. keyTimes这个可选参数可以为对应的关键帧指定对应的时间点,其取值范围为0到1.0,keyTimes中的每一个时间值都对应values中的每一帧.当keyTimes没有设置的时候,各个关键帧的时间是平分的.
//    还可以通过设置可选参数timingFunctions(CAKeyframeAnimation中timingFunction是无效的)为关键帧之间的过渡设置timingFunction,如果values有n个元素,那么timingFunctions则应该有n-1个.但很多时候并不需要timingFunctions,因为已经设置了够多的关键帧了,比如没1/60秒就设置了一个关键帧,那么帧率将达到60FPS,完全不需要相邻两帧的过渡效果（当然也有可能某两帧 值相距较大,可以使用均匀变化或者增加帧率,比如每0.01秒设置一个关键帧）.
//    
//    在关键帧动画中还有一个非常重要的参数,那便是calculationMode,计算模式.其主要针对的是每一帧的内容为一个座标点的情况,也就是对anchorPoint 和 position 进行的动画.当在平面座标系中有多个离散的点的时候,可以是离散的,也可以直线相连后进行插值计算,也可以使用圆滑的曲线将他们相连后进行插值计算. calculationMode目前提供如下几种模式 kCAAnimationLinear
//    kCAAnimationDiscrete
//    kCAAnimationPaced
//    kCAAnimationCubic
//    kCAAnimationCubicPaced
//    
//    kCAAnimationLinear calculationMode的默认值,表示当关键帧为座标点的时候,关键帧之间直接直线相连进行插值计算;
//    kCAAnimationDiscrete 离散的,就是不进行插值计算,所有关键帧直接逐个进行显示;
//    kCAAnimationPaced 使得动画均匀进行,而不是按keyTimes设置的或者按关键帧平分时间,此时keyTimes和timingFunctions无效;
//    kCAAnimationCubic 对关键帧为座标点的关键帧进行圆滑曲线相连后插值计算,对于曲线的形状还可以通过tensionValues,continuityValues,biasValues来进行调整自定义,这里的数学原理是Kochanek–Bartels spline,这里的主要目的是使得运行的轨迹变得圆滑;
//    kCAAnimationCubicPaced 看这个名字就知道和kCAAnimationCubic有一定联系,其实就是在kCAAnimationCubic的基础上使得动画运行变得均匀,就是系统时间内运动的距离相同,此时keyTimes以及timingFunctions也是无效的.
//    CGRect boundingRect = CGRectMake(-150, -150, 300, 300);
//    
//    CAKeyframeAnimation *orbit = [CAKeyframeAnimation animation];
//    orbit.keyPath = @"position";
//    orbit.path = CFAutorelease(CGPathCreateWithEllipseInRect(boundingRect, NULL));
//    orbit.duration = 4;
//    orbit.additive = YES;
//    orbit.repeatCount = HUGE_VALF;
//    orbit.calculationMode = kCAAnimationRotateAutoReverse;
//    orbit.rotationMode = kCAAnimationRotateAuto;
//    
//    [demoView.layer addAnimation:orbit forKey:@"orbit"];
    
    

    CAKeyframeAnimation *animation = [CAKeyframeAnimation animation];
    animation.keyPath = @"position.x";
    animation.values = @[ @0, @10, @-10, @10, @0 ];
    animation.keyTimes = @[ @0, @(1 / 6.0), @(3 / 6.0), @(5 / 6.0), @1 ];
    animation.duration = 0.4;
    animation.repeatCount = HUGE_VALF;
    animation.additive = YES;
    
    [demoView.layer addAnimation:animation forKey:@"shake"];
    
}

-(void)Pualse {
    if (!flag) {
        [CoreAnimations pauseLayer:demoView.layer];
        flag = YES;
    }else {
        [CoreAnimations resumeLayer:demoView.layer];
        flag = NO;
    }
    
    
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
