![](https://lh3.googleusercontent.com/-E3mEbRoTpuI/Vul9SIAGMnI/AAAAAAAAOPs/-M7f6O1Rw10waBBd5zjpzPmg0KIiQQkOA/s0/message-queue.png)
**message-queue** is a simple example about using message queue to send and receive data cross process, in current version I just support windows, I will write a demo for linux if I have free time. This project solve a simple math: we have two processes p1 and p2, p1 will open a file to read math expression in each line then send to p2 to solve this expression. After that, p2 response result to p1, p1 will write the result to another file.
## Installation
Current projects has been developed on [Visual Studio](https://www.visualstudio.com/), include three projects are:

1. sender: This is process one(p1), open file then read each line(math expression) to send to receiver, wait for result from receiver process to write result to another file.
2. receiver: This is a process two(p2), wait for a math expression from sender process. When this process received the expression, solve it and response result to sender process.
3. shared: A library project to share some common code and define.

P1 and P2 will using the message queue to receive message from other, to send a message to other we using SendMessage function(in win32).

> In win32, a message queue was created by create a Window, then we using WinProc to receive message from other and a message loop to keep window alive. To send message to other we will using SendMessage function with a window handle, especially, you must use WM_COPYDATA and a COPYDATASTRUCT to pass your data from a process to another.

## Usage
So easy! just download project then open with [Visual Studio](https://www.visualstudio.com/) then rebuild shared project first, after that you just press F5 to run receiver and sender to see result.

**Note 1**: You must change two define to your own file paths before run sender and receiver
``` cpp
#define INPUT_FILENAME		"in.txt" /* input file which contains math expressions */
#define OUTPUT_FILENAME		"out.txt" /* output file which will contain results */
```

**Note 2**:  You have to start receiver before start sender because receiver must be initialized to take a message queue then wait for data from sender, after that sender will auto find receiver's window handle to send message to it.

This is some screenshots from sender, receiver and files:

*Sender console*

![](https://lh3.googleusercontent.com/-vX_QyQU4NEs/VumEvxt-iXI/AAAAAAAAOQE/xqhDRYB5D9AX3zv5icfcuHmtmtBb2LMoQ/s0/s.PNG)

*Receiver console*

![](https://lh3.googleusercontent.com/-R8b1QysAU1o/VumFBtNVSFI/AAAAAAAAOQU/nIsBLhzii7cMpWUnNPFKiRhQFssL21eyA/s0/r.PNG)

*Input and ouput files*

![](https://lh3.googleusercontent.com/-GPL9ztzODhY/VumFLnD0hWI/AAAAAAAAOQk/6NIDcDITEfcZwn-2E0pom_4cc_jibz9ug/s0/Capture.PNG)

## Contributing
1. Fork it!
2. Create your feature branch: `git checkout -b my-new-feature`
3. Commit your changes: `git commit -am 'Add some feature'`
4. Push to the branch: `git push origin my-new-feature`
5. Submit a pull request :D

##Dependencies
This project not required the dependencies.
## History
Version 1.0.0 is just a simple message queue for win32
## Author
Developed by sontx/noem, some useful information:

 - Home: [www.code4bugs.com](www.code4bugs.com)
 - My blog: [www.sontx.blogspot.com](http://www.sontx.blogspot.com)
 - Email: <a href="mailto:xuanson33bk@gmail.com">xuanson33bk@gmail.com</a>
 - Facebook: [No Em](https://mobile.facebook.com/noem.bk)

## License
Copyright 2016 Tran Xuan Son
