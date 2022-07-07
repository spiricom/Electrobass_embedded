# Electrobass_embedded
Code for the three microcontrollers in the Electrobass hardware

## Changing name of an STMCube32 project 
https://community.st.com/s/question/0D53W000004Htp3SAC/change-the-name-of-the-project-in-stm32cubeide

1. Change name in `.project` file
2. Change directory name 
3. File->Import->existing project into workspace
4. click copy projects into workspace

## Adding LEAF after pull
1. right-click the leaf folder in the STMCube32IDE and go to properties (leaf->properties)
2. Under C/C++ Build->settings unclick `Exclude resource from build`
3. right-click the top level project and go to properties (project->properties)
3. Under C/C++ Build->settings->MCU GCC Compiler->Include Paths Add your leaf directory