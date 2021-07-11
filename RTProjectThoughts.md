Log 3 ________________
My code is undeniably messy. After having to translate from C++ (and I ended up scrapping the idea of malloc-ing data because it felt like the life span of most vectors stayed in a loop), it leaves much to be desired in terms of bringing out the strengths in C.

I at least tried passing by reference instead of passing by value to avoid copying copious amounts of data.

The other thing that the tutorial I followed did that C++ has is operator overloading. I wish I had that, it would make reading my code so much easier.

I ended up stopping after a certain point once I was able to render simple spheres with a simple lighting model. The next step after this used classes and other spicy C++ stuff that would be a pain to translate to C.

I also could see lots of improvement in my code, cleaning up redundant code and making things more efficient overall, but I will stop here.

Log 2 ________________
After making vectors to be malloc-ed, I realize that maybe passing by value is the play here. Since I'm looping over each pixel and the life span of most vectors only is through that loop, it'll automatically be pulled off the stack, right?

So perhaps the use of malloc may be unnecessary with the way I was thinking it was going to be used, but there's probably a use for it that I have been overlooking.

Log 1 ________________
I realize why I just had the issue of calculating incorrect normals.

This is because in my vector multiply function in vec3.c, modified the pointer parameter (which was a vector) and returned that same pointer. This messed up further calculations!