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
#include <regex>

using namespace netstress;

bool CmdLine::Parse(int argc, wchar_t* argv[])
{
	bool retVal = true;

	for (int argi = 1; argi < argc; ++argi)
	{
		std::wstring_view arg{ argv[argi] };
		if (arg.size() < 1) continue;

		if (arg[0] == L'-')
		{
			std::transform(arg.begin(), arg.end(), argv[argi], towlower);

			if (arg == L"-help" || arg == L"--help" || arg == L"-?")
			{
				retVal = false;
				break;

			}
			else if (arg == L"-host")
			{
				++argi;
				if (argi >= argc)
				{
					std::cerr << "ERROR: Expected argument to '-host' missing" << std::endl;
					retVal = false;
					break;
				}

				std::wregex host{
					LR"(^(?:(\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3})|(?:\[([0-9a-f:]+)\])|([a-z0-9-]+))(?::(\d+))?$)",
					std::regex_constants::ECMAScript | std::regex_constants::icase
				};
				std::wcmatch match;
				if (std::regex_match(argv[argi], match, host))
				{
					if (match[1].matched)
					{
						m_hostAddr = match[1].str();
					}
					else if (match[2].matched)
					{
						m_hostAddr = match[2].str();
					}
					else if (match[3].matched)
					{
						m_hostAddr = match[3].str();
					}
					else
					{
						m_hostAddr = L"0.0.0.0";
					}

					if (match[4].matched)
					{
						m_hostPort = static_cast<unsigned int>(std::stoi(match[4].str()));
					}

				}
				else
				{
					std::cerr << "FAILED to parse '-host' argument string" << std::endl;
					retVal = false;
					continue;
				}

			}
			else if (arg == L"-connect")
			{
				++argi;
				if (argi >= argc)
				{
					std::cerr << "ERROR: Expected argument to '-connect' missing" << std::endl;
					retVal = false;
					break;
				}

				std::wregex host{
					LR"(^(?:(\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3})|(?:\[([0-9a-f:]+)\])|([a-z0-9-]+))(?::(\d+))?$)",
					std::regex_constants::ECMAScript | std::regex_constants::icase
				};
				std::wcmatch match;
				if (std::regex_match(argv[argi], match, host))
				{
					if (match[1].matched)
					{
						m_connectAddr = match[1].str();
					}
					else if (match[2].matched)
					{
						m_connectAddr = match[2].str();
					}
					else if (match[3].matched)
					{
						m_connectAddr = match[3].str();
					}
					else
					{
						m_connectAddr.clear();
					}

					if (match[4].matched)
					{
						m_connectPort = static_cast<unsigned int>(std::stoi(match[4].str()));
					}

				}
				else
				{
					std::cerr << "FAILED to parse '-connect' argument string" << std::endl;
					retVal = false;
					continue;
				}

			}
			else if (arg == L"-gui")
			{
				m_showGui = true;
			}
			else if (arg == L"-send")
			{

				// TODO: Implement

				std::wcerr << L"Command '-send' is not implemented, yet." << std::endl;
				retVal = false;

			}
			else
			{
				std::wcerr << L"Unexpected command argument ignored: " << arg << std::endl;
				retVal = false;
				continue;
			}
		}
		else
		{
			std::wcerr << L"Unexpected argument ignored: " << arg << std::endl;
			retVal = false;
			continue;
		}
	}

	return retVal;
}

void CmdLine::PrintHelp() const
{
	std::cout << R"(
NetStress Tool Command Line Options

Syntax:
	netstress.exe (-host (<IP>)(:<port>)) (-connect <IP>(:<port>)) (-gui) (-send <TBD>)

Options:
  -host
	Opens a server port on the device with the specified IP.
	If omitted, "0.0.0.0" is assumed, and the port is opened for all devices.
	The address can be specified as name or numerically in IPv4 or IPv6 (in brackets, e.g.: "[2001:0db8:85a3:08d3::0370:7344]", like URL notation).
	If the port is omitted, the default port ()" << DefaultPort << R"() is assumed.
	You must specify either the address or the port (prefixed by ':') or both.
  -connect
	Connects to a remote server port on the specified address.
	The address can be specified as name or numerically in IPv4 or IPv6 (in brackets, e.g.: "[2001:0db8:85a3:08d3::0370:7344]", like URL notation).
	If the port is omitted, the default port ()" << DefaultPort << R"() is assumed.
  -gui
	Opens a window showing a graphical interface.
  -send
	TODO
	Specifies bandwidth and send rate to be sent from this node to the connected node.
)" << std::endl;
}
