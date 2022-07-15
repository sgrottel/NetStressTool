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
#pragma once

#include <string>

namespace netstress
{

	class CmdLine
	{
	public:
		static constexpr const unsigned int DefaultPort{ 5544 };

		bool Parse(int argc, wchar_t* argv[]);
		void PrintHelp() const;

		inline std::wstring const& GetHostAddress() const
		{
			return m_hostAddr;
		}
		inline unsigned int GetHostPort() const
		{
			return m_hostPort;
		}
		inline std::wstring const& GetConnectAddress() const
		{
			return m_connectAddr;
		}
		inline unsigned int GetConnectPort() const
		{
			return m_connectPort;
		}
		inline bool GetShowGui() const
		{
			return m_showGui;
		}

	private:
		std::wstring m_hostAddr{ L"0.0.0.0" };
		unsigned int m_hostPort{ DefaultPort };
		std::wstring m_connectAddr{};
		unsigned int m_connectPort{ DefaultPort };
		bool m_showGui{ false };

	};

}
