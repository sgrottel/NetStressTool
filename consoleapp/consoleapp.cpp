// Copyright 2022 SGrottel
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissionsand
// limitations under the License.
#include "CmdLine.h"


#include <iostream>

int wmain(int argc, wchar_t* argv[])
{
    try
    {
        netstress::CmdLine cmd;
        if (!cmd.Parse(argc, argv))
        {
            cmd.PrintHelp();
            return 0;
        }


        std::cout << "Hello World!\n";


    }
    catch (std::exception const& ex)
    {
        std::cerr << L"EXCEPTION: " << ex.what() << std::endl;
        return -1;
    }
    catch (...)
    {
        std::cerr << L"EXCEPTION: unknown exception" << std::endl;
        return -1;
    }

    return 0;
}
