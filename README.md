# App Runner

Small application expecting a .dll for rendering and the logic.

These should be similar to [ubrotengine-dx11](https://github.com/rwarnking/ubrotengine-dx11).

## Style Guide

C style pointer are discouraged and therefore either the
std-smartpointer or the Microsoft::WRL::ComPtr (wrl\client.h) should be used.
Since such pointer either succeed or throw an exception
there is no need to check for nullptr afterwards. 
Click [here](https://stackoverflow.com/questions/57089737/need-to-check-for-nullptr-when-make-shared-and-make-unique-is-used) for details.
