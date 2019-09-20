
### Visual Studio 2017 Open Folder Project:  
#### Build, Move to remote, and Debug.  

This project shows configuration settings needed to use the AXC2152 SDK in conjunction with Visual Studio 2017.  

#### CppProperties.json  
  This file sets the environment variables (sysroot location, output name, build path), as well as information such as include paths to help Intellisense understand your references to get the full IDE experience.  
  
#### /.vs/tasks.vs.json 
  This file has two tasks in it.  They are accessible by right clicking the main solution folder in the "Solution Explorer" pane:  
    * **AXC2152 Build**  
       This task uses the environment variables in CppProperties.json and compiles the code by executing the SDK's GCC with needed flags. Note, as you add references and code, flags may need to be included here.  This task will show up in the right-click context menu as "Build".  
    * **Move To Remote**  
       This task uses PuTTy command line services to move the compiled output to the AXC2152. Note that you may need to change login/pw and remote folder settings to fit your system.  This task will show up in the right-click context menu as "Move to Remote".  
       
#### /.vs/tasks.vs.json  
  This file has all of the remote debugger settings in it. Note that you may need to modify user/pw and path names to fit your application.  This can also be accessed by right clicking the main solution folder.  It will show up in the context menu as "Debug". Be sure to have your breakpoints in place before running the debug.  
