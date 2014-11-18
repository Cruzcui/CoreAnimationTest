//
//  CoreAnimations.h
//  CoreAnimationTest
//
//  Created by ishang on 14/11/17.
//  Copyright (c) 2014年 commondec. All rights reserved.
//
//时间系统
//CALayer实现了CAMediaTiming协议. CALayer通过CAMediaTiming协议实现了一个有层级关系的时间系统.除了CALayer,CAAnimation也采纳了此协议,用来实现动画的时间系统.
//在CA中,有一个Absolute Time(绝对时间)的概念,可以通过CACurrentMediaTime()获得,其实这个绝对时间就是将mach_absolute_time()转换成秒后的值.这个时间和系统的uptime有关,系统重启后CACurrentMediaTime()会被重置.
//就和座标存在相对座标一样,不同的实现了CAMediaTiming协议的存在层级关系的对象也存在相对时间,经常需要进行时间的转换,CALayer提供了两个时间转换的方法:
//- (CFTimeInterval)convertTime:(CFTimeInterval)t fromLayer:(CALayer *)l;
//- (CFTimeInterval)convertTime:(CFTimeInterval)t toLayer:(CALayer *)l;
//现在来重点研究CAMediaTiming协议中几个重要的属性.
//beginTime
//无论是图层还是动画,都有一个时间线Timeline的概念,他们的beginTime是相对于父级对象的开始时间. 虽然苹果的文档中没有指明,但是通过代码测试可以发现,默认情况下所有的CALayer图层的时间线都是一致的,他们的beginTime都是0,绝对时间转换到当前Layer中的时间大小就是绝对时间的大小.所以对于图层而言,虽然创建有先后,但是他们的时间线都是一致的(只要不主动去修改某个图层的beginTime),所以我们可以想象成所有的图层默认都是从系统重启后开始了他们的时间线的计时.
//但是动画的时间线的情况就不同了,当一个动画创建好,被加入到某个Layer的时候,会先被拷贝一份出来用于加入当前的图层,在CA事务被提交的时候,如果图层中的动画的beginTime为0,则beginTime会被设定为当前图层的当前时间,使得动画立即开始.如果你想某个直接加入图层的动画稍后执行,可以通过手动设置这个动画的beginTime,但需要注意的是这个beginTime需要为 CACurrentMediaTime()+延迟的秒数,因为beginTime是指其父级对象的时间线上的某个时间,这个时候动画的父级对象为加入的这个图层,图层当前的时间其实为[layer convertTime:CACurrentMediaTime() fromLayer:nil],其实就等于CACurrentMediaTime(),那么再在这个layer的时间线上往后延迟一定的秒数便得到上面的那个结果.
//timeOffset
//这个timeOffset可能是这几个属性中比较难理解的一个,官方的文档也没有讲的很清楚. local time也分成两种一种是active local time 一种是basic local time.
//timeOffset则是active local time的偏移量.
//你将一个动画看作一个环,timeOffset改变的其实是动画在环内的起点,比如一个duration为5秒的动画,将timeOffset设置为2(或者7,模5为2),那么动画的运行则是从原来的2秒开始到5秒,接着再0秒到2秒,完成一次动画.
//speed
//speed属性用于设置当前对象的时间流相对于父级对象时间流的流逝速度,比如一个动画beginTime是0,但是speed是2,那么这个动画的1秒处相当于父级对象时间流中的2秒处. speed越大则说明时间流逝速度越快,那动画也就越快.比如一个speed为2的layer其所有的父辈的speed都是1,它有一个subLayer,speed也为2,那么一个8秒的动画在这个运行于这个subLayer只需2秒(8 / (2 * 2)).所以speed有叠加的效果.
//fillMode
//fillMode的作用就是决定当前对象过了非active时间段的行为. 比如动画开始之前,动画结束之后。如果是一个动画CAAnimation,则需要将其removedOnCompletion设置为NO,要不然fillMode不起作用. 下面来讲各个fillMode的意义
//kCAFillModeRemoved 这个是默认值,也就是说当动画开始前和动画结束后,动画对layer都没有影响,动画结束后,layer会恢复到之前的状态
//kCAFillModeForwards 当动画结束后,layer会一直保持着动画最后的状态
//kCAFillModeBackwards 这个和kCAFillModeForwards是相对的,就是在动画开始前,你只要将动画加入了一个layer,layer便立即进入动画的初始状态并等待动画开始.你可以这样设定测试代码,将一个动画加入一个layer的时候延迟5秒执行.然后就会发现在动画没有开始的时候,只要动画被加入了layer,layer便处于动画初始状态
//kCAFillModeBoth 理解了上面两个,这个就很好理解了,这个其实就是上面两个的合成.动画加入后开始之前,layer便处于动画初始状态,动画结束后layer保持动画最后的状态.
//其他的一些参数都是比较容易理解的.
#import <Foundation/Foundation.h>
#import <QuartzCore/QuartzCore.h>
@interface CoreAnimations : NSObject
+(CABasicAnimation *)opacityForever_Animation:(float)time;//永久闪烁动画
+(CABasicAnimation *)opacityTimes_Animation:(float)repeatTimes durTimes:(float)time;//有闪烁次数的动画
+(CABasicAnimation *)moveX:(float)time X:(NSNumber *)x;//横向移动
+(CABasicAnimation *)moveY:(float)time Y:(NSNumber *)y;//纵向移动
+(CABasicAnimation * )scale:(NSNumber *)Multiple orgin:(NSNumber *)orginMultiple durTimes:(float)time Rep:(float)repeatTimes; //缩放
+(CAAnimationGroup *)groupAnimation:(NSArray *)animationAry durTimes:(float)time Rep:(float)repeatTimes;//组合动画
+(CAKeyframeAnimation *) keyframeAnimation:(CGMutablePathRef)path durTimes:(float)time Rep:(float)repeatTimes;//路径动画

+(void)pauseLayer:(CALayer*)layer;//暂停动画
+(void)resumeLayer:(CALayer*)layer;//继续动画






















@end
