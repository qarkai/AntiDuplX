/*
* AntiDuplX utility (http://github.com/ermig1979/AntiDuplX).
*
* Copyright (c) 2023-2023 Yermalayeu Ihar.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#include "AntiDuplX/AdxEngine.h"

namespace Adx
{
	Engine::Engine(const Options& options)
		: _options(options)
		, _imageFinder(options, _imageInfos)
		, _imageMatcher(options, _imageInfos)
	{
	}

	bool Engine::Run()
	{
		CPL_LOG_SS(Info, "Start search of duplicates:");

		if (!_imageFinder.Run())
			return false;

		if (!_imageMatcher.Run())
			return false;

		Print();

		return true;
	}

	void Engine::Print()
	{
		std::cout << "Image count: " << _imageInfos.size() << std::endl;
		for (size_t i = 0; i < _imageInfos.size(); ++i)
		{
			const ImageInfo& info = _imageInfos[i];
			std::cout << info.path << " ";
			std::cout << info.size / 1024 << " kb ";
			std::cout << "[" << info.width << "x" << info.height << "] ";
			//std::cout << ToStr(info.format)<< " ";
			std::cout << (info.remove ? "~~~ REMOVE ~~~" : "" );
			std::cout << std::endl;
		}
	}
}
