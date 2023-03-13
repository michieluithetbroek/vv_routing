//
//  main.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 12/03/2023.
//

#include <iostream>

#include "./initOSM/initOSM.h"

int main(int argc, const char * argv[])
{
    InitOSM doei;
    
    doei.print_nodes();
    //doei.print_nodes_csv();
    
}
