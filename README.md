# ENEE 645 Constant Argument Instatiate Project

## Team members:
    
    - Runzhi Xing
    - Jiahao Wu

## Deliverable List:

1. Human readable IR produced by our pass:
    
    1). `example1.hello.ll`

    2). `example2.hello.ll`

    3). `example3.hello.ll`

    4). `example4.hello.ll`

2. Source code:
    
    `lib/FuncInst/funcInst.cpp`

3. Makefiles: We started from the sample source code directory, so we only made changes in sample/lib/..., therefore, our deliverable conatains only lib directory and Makefiles inside lib directory. Other makefiles we didn't make any changes.
    
    `lib/Makefile`
    `lib/FuncInst/Makefile`

4. To remove dead arguments from functions. We used the `deadargelim` pass separately on the command line.

```shell
opt --deadargelim < input bytecode > -o < output byte code >
```

## The second method:

We explored two methods to do constant argument instantiation. The code descirbed above follows the steps from project description. The second method we used VMap at the Function Clone step. We attched the second method as an archived file in the deliverable as well.

## Comparison:

According to our experiment, hey both are able to instatiate the constant arguments. And we compiled the IR after the constant argument instatiation to executable, they printed out the same results are the orginal program. Then we used `diff` command to compare the difference between two IRs, then we found the following difference by running 

`diff example4.fisrtmethod.ll example4.secondmethod.ll`:

```diff
32 @diff1(i32 %5) #0
---
>   %6 = call i32 @diff1(i32 %5)
63c63
<   %4 = call i32 @randomStuff2(i32 %2, i32 %3) #0
---
>   %4 = call i32 @randomStuff2(i32 %2, i32 %3)
66c66
<   %6 = call i32 @randomStuff3(i32 %5) #0
---
>   %6 = call i32 @randomStuff3(i32 %5)
108c108
<   %6 = call i32 @diff1(i32 %5) #0
---
>   %6 = call i32 @diff1(i32 %5)
135c135
<   %6 = call i32 @diff1(i32 %5) #0
---
>   %6 = call i32 @diff1(i32 %5)
```

Basiclly, the difference is that the second method adds an extra `#0` at each call-site. Except this, other IR codes are the same. And both IRs can produce correct result after being compiled to executable.
