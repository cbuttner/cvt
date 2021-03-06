/*
   The MIT License (MIT)

   Copyright (c) 2011 - 2013, Philipp Heise and Sebastian Klose

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
*/

#include <cvt/vision/features/agast/OAST9_16.h>
#include <cvt/gfx/IMapScoped.h>

namespace cvt
{
    OAST9_16::OAST9_16() :
        _lastStride( 0 )
    {
    }

    OAST9_16::~OAST9_16()
    {
    }

    //
    //    oast9 - OAST, an optimal corner detector based on the
    //              accelerated segment test for a 16 pixel mask
    //
    //    Copyright (C) 2010  Elmar Mair
    //    All rights reserved.
    //
    //    Redistribution and use in source and binary forms, with or without
    //    modification, are permitted provided that the following conditions are met:
    //        * Redistributions of source code must retain the above copyright
    //          notice, this list of conditions and the following disclaimer.
    //        * Redistributions in binary form must reproduce the above copyright
    //          notice, this list of conditions and the following disclaimer in the
    //          documentation and/or other materials provided with the distribution.
    //        * Neither the name of the <organization> nor the
    //          names of its contributors may be used to endorse or promote products
    //          derived from this software without specific prior written permission.
    //
    //    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
    //    ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    //    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    //    DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
    //    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    //    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    //    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    //    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    //    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    //    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

    void OAST9_16::detect( const Image& img, uint8_t threshold, FeatureSetWrapper& features, size_t border )
    {
        IMapScoped<const uint8_t> map( img );
        if( map.stride() != _lastStride ){
            _lastStride = map.stride();
            updateOffsets();
        }

        size_t x, y;
        size_t xsizeB = img.width() - border;
        size_t ysizeB = img.height() - border;

        const uint8_t* im = map.ptr();
        for( y = border; y < ysizeB; y++ ) {
            x = border - 1;
            while( 1 ){
                x++;
                if( x > xsizeB ){
                    break;
                } else {
                    const uint8_t* const p = im + y * map.stride() + x;
                    const int cb = (int)*p + threshold;
                    const int c_b = (int)*p - threshold;
                    if(p[offset0] > cb)
                        if(p[offset2] > cb)
                            if(p[offset4] > cb)
                                if(p[offset5] > cb)
                                    if(p[offset7] > cb)
                                        if(p[offset3] > cb)
                                            if(p[offset1] > cb)
                                                if(p[offset6] > cb)
                                                    if(p[offset8] > cb)
                                                    {}
                                                    else
                                                        if(p[offset15] > cb)
                                                        {}
                                                        else
                                                            continue;
                                                else
                                                    if(p[offset13] > cb)
                                                        if(p[offset14] > cb)
                                                            if(p[offset15] > cb)
                                                            {}
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                            else
                                                if(p[offset8] > cb)
                                                    if(p[offset9] > cb)
                                                        if(p[offset10] > cb)
                                                            if(p[offset6] > cb)
                                                            {}
                                                            else
                                                                if(p[offset11] > cb)
                                                                    if(p[offset12] > cb)
                                                                        if(p[offset13] > cb)
                                                                            if(p[offset14] > cb)
                                                                                if(p[offset15] > cb)
                                                                                {}
                                                                                else
                                                                                    continue;
                                                                            else
                                                                                continue;
                                                                        else
                                                                            continue;
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                        else
                                            if(p[offset10] > cb)
                                                if(p[offset11] > cb)
                                                    if(p[offset12] > cb)
                                                        if(p[offset8] > cb)
                                                            if(p[offset9] > cb)
                                                                if(p[offset6] > cb)
                                                                {}
                                                                else
                                                                    if(p[offset13] > cb)
                                                                        if(p[offset14] > cb)
                                                                            if(p[offset15] > cb)
                                                                            {}
                                                                            else
                                                                                continue;
                                                                        else
                                                                            continue;
                                                                    else
                                                                        continue;
                                                            else
                                                                if(p[offset1] > cb)
                                                                    if(p[offset13] > cb)
                                                                        if(p[offset14] > cb)
                                                                            if(p[offset15] > cb)
                                                                            {}
                                                                            else
                                                                                continue;
                                                                        else
                                                                            continue;
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                        else
                                                            if(p[offset1] > cb)
                                                                if(p[offset13] > cb)
                                                                    if(p[offset14] > cb)
                                                                        if(p[offset15] > cb)
                                                                        {}
                                                                        else
                                                                            continue;
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                    else if(p[offset7] < c_b)
                                        if(p[offset14] > cb)
                                            if(p[offset15] > cb)
                                                if(p[offset1] > cb)
                                                    if(p[offset3] > cb)
                                                        if(p[offset6] > cb)
                                                        {}
                                                        else
                                                            if(p[offset13] > cb)
                                                            {}
                                                            else
                                                                continue;
                                                    else
                                                        if(p[offset10] > cb)
                                                            if(p[offset11] > cb)
                                                                if(p[offset12] > cb)
                                                                    if(p[offset13] > cb)
                                                                    {}
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                else
                                                    if(p[offset8] > cb)
                                                        if(p[offset9] > cb)
                                                            if(p[offset10] > cb)
                                                                if(p[offset11] > cb)
                                                                    if(p[offset12] > cb)
                                                                        if(p[offset13] > cb)
                                                                        {}
                                                                        else
                                                                            continue;
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                            else
                                                continue;
                                        else if(p[offset14] < c_b)
                                            if(p[offset8] < c_b)
                                                if(p[offset9] < c_b)
                                                    if(p[offset10] < c_b)
                                                        if(p[offset11] < c_b)
                                                            if(p[offset12] < c_b)
                                                                if(p[offset13] < c_b)
                                                                    if(p[offset6] < c_b)
                                                                    {}
                                                                    else
                                                                        if(p[offset15] < c_b)
                                                                        {}
                                                                        else
                                                                            continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                    else
                                        if(p[offset14] > cb)
                                            if(p[offset15] > cb)
                                                if(p[offset1] > cb)
                                                    if(p[offset3] > cb)
                                                        if(p[offset6] > cb)
                                                        {}
                                                        else
                                                            if(p[offset13] > cb)
                                                            {}
                                                            else
                                                                continue;
                                                    else
                                                        if(p[offset10] > cb)
                                                            if(p[offset11] > cb)
                                                                if(p[offset12] > cb)
                                                                    if(p[offset13] > cb)
                                                                    {}
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                else
                                                    if(p[offset8] > cb)
                                                        if(p[offset9] > cb)
                                                            if(p[offset10] > cb)
                                                                if(p[offset11] > cb)
                                                                    if(p[offset12] > cb)
                                                                        if(p[offset13] > cb)
                                                                        {}
                                                                        else
                                                                            continue;
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                else if(p[offset5] < c_b)
                                    if(p[offset12] > cb)
                                        if(p[offset13] > cb)
                                            if(p[offset14] > cb)
                                                if(p[offset15] > cb)
                                                    if(p[offset1] > cb)
                                                        if(p[offset3] > cb)
                                                        {}
                                                        else
                                                            if(p[offset10] > cb)
                                                                if(p[offset11] > cb)
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                    else
                                                        if(p[offset8] > cb)
                                                            if(p[offset9] > cb)
                                                                if(p[offset10] > cb)
                                                                    if(p[offset11] > cb)
                                                                    {}
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                else
                                                    if(p[offset6] > cb)
                                                        if(p[offset7] > cb)
                                                            if(p[offset8] > cb)
                                                                if(p[offset9] > cb)
                                                                    if(p[offset10] > cb)
                                                                        if(p[offset11] > cb)
                                                                        {}
                                                                        else
                                                                            continue;
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                    else if(p[offset12] < c_b)
                                        if(p[offset7] < c_b)
                                            if(p[offset8] < c_b)
                                                if(p[offset9] < c_b)
                                                    if(p[offset10] < c_b)
                                                        if(p[offset11] < c_b)
                                                            if(p[offset13] < c_b)
                                                                if(p[offset6] < c_b)
                                                                {}
                                                                else
                                                                    if(p[offset14] < c_b)
                                                                        if(p[offset15] < c_b)
                                                                        {}
                                                                        else
                                                                            continue;
                                                                    else
                                                                        continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                    else
                                        continue;
                                else
                                    if(p[offset12] > cb)
                                        if(p[offset13] > cb)
                                            if(p[offset14] > cb)
                                                if(p[offset15] > cb)
                                                    if(p[offset1] > cb)
                                                        if(p[offset3] > cb)
                                                        {}
                                                        else
                                                            if(p[offset10] > cb)
                                                                if(p[offset11] > cb)
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                    else
                                                        if(p[offset8] > cb)
                                                            if(p[offset9] > cb)
                                                                if(p[offset10] > cb)
                                                                    if(p[offset11] > cb)
                                                                    {}
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                else
                                                    if(p[offset6] > cb)
                                                        if(p[offset7] > cb)
                                                            if(p[offset8] > cb)
                                                                if(p[offset9] > cb)
                                                                    if(p[offset10] > cb)
                                                                        if(p[offset11] > cb)
                                                                        {}
                                                                        else
                                                                            continue;
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                    else if(p[offset12] < c_b)
                                        if(p[offset7] < c_b)
                                            if(p[offset8] < c_b)
                                                if(p[offset9] < c_b)
                                                    if(p[offset10] < c_b)
                                                        if(p[offset11] < c_b)
                                                            if(p[offset13] < c_b)
                                                                if(p[offset14] < c_b)
                                                                    if(p[offset6] < c_b)
                                                                    {}
                                                                    else
                                                                        if(p[offset15] < c_b)
                                                                        {}
                                                                        else
                                                                            continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                    else
                                        continue;
                            else if(p[offset4] < c_b)
                                if(p[offset11] > cb)
                                    if(p[offset12] > cb)
                                        if(p[offset13] > cb)
                                            if(p[offset10] > cb)
                                                if(p[offset14] > cb)
                                                    if(p[offset15] > cb)
                                                        if(p[offset1] > cb)
                                                        {}
                                                        else
                                                            if(p[offset8] > cb)
                                                                if(p[offset9] > cb)
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                    else
                                                        if(p[offset6] > cb)
                                                            if(p[offset7] > cb)
                                                                if(p[offset8] > cb)
                                                                    if(p[offset9] > cb)
                                                                    {}
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                else
                                                    if(p[offset5] > cb)
                                                        if(p[offset6] > cb)
                                                            if(p[offset7] > cb)
                                                                if(p[offset8] > cb)
                                                                    if(p[offset9] > cb)
                                                                    {}
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                            else
                                                if(p[offset1] > cb)
                                                    if(p[offset3] > cb)
                                                        if(p[offset14] > cb)
                                                            if(p[offset15] > cb)
                                                            {}
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                        else
                                            continue;
                                    else
                                        continue;
                                else if(p[offset11] < c_b)
                                    if(p[offset7] < c_b)
                                        if(p[offset8] < c_b)
                                            if(p[offset9] < c_b)
                                                if(p[offset10] < c_b)
                                                    if(p[offset6] < c_b)
                                                        if(p[offset5] < c_b)
                                                            if(p[offset3] < c_b)
                                                            {}
                                                            else
                                                                if(p[offset12] < c_b)
                                                                {}
                                                                else
                                                                    continue;
                                                        else
                                                            if(p[offset12] < c_b)
                                                                if(p[offset13] < c_b)
                                                                    if(p[offset14] < c_b)
                                                                    {}
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                    else
                                                        if(p[offset12] < c_b)
                                                            if(p[offset13] < c_b)
                                                                if(p[offset14] < c_b)
                                                                    if(p[offset15] < c_b)
                                                                    {}
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                    else
                                        continue;
                                else
                                    continue;
                            else
                                if(p[offset11] > cb)
                                    if(p[offset12] > cb)
                                        if(p[offset13] > cb)
                                            if(p[offset10] > cb)
                                                if(p[offset14] > cb)
                                                    if(p[offset15] > cb)
                                                        if(p[offset1] > cb)
                                                        {}
                                                        else
                                                            if(p[offset8] > cb)
                                                                if(p[offset9] > cb)
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                    else
                                                        if(p[offset6] > cb)
                                                            if(p[offset7] > cb)
                                                                if(p[offset8] > cb)
                                                                    if(p[offset9] > cb)
                                                                    {}
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                else
                                                    if(p[offset5] > cb)
                                                        if(p[offset6] > cb)
                                                            if(p[offset7] > cb)
                                                                if(p[offset8] > cb)
                                                                    if(p[offset9] > cb)
                                                                    {}
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                            else
                                                if(p[offset1] > cb)
                                                    if(p[offset3] > cb)
                                                        if(p[offset14] > cb)
                                                            if(p[offset15] > cb)
                                                            {}
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                        else
                                            continue;
                                    else
                                        continue;
                                else if(p[offset11] < c_b)
                                    if(p[offset7] < c_b)
                                        if(p[offset8] < c_b)
                                            if(p[offset9] < c_b)
                                                if(p[offset10] < c_b)
                                                    if(p[offset12] < c_b)
                                                        if(p[offset13] < c_b)
                                                            if(p[offset6] < c_b)
                                                                if(p[offset5] < c_b)
                                                                {}
                                                                else
                                                                    if(p[offset14] < c_b)
                                                                    {}
                                                                    else
                                                                        continue;
                                                            else
                                                                if(p[offset14] < c_b)
                                                                    if(p[offset15] < c_b)
                                                                    {}
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                    else
                                        continue;
                                else
                                    continue;
                        else if(p[offset2] < c_b)
                            if(p[offset9] > cb)
                                if(p[offset10] > cb)
                                    if(p[offset11] > cb)
                                        if(p[offset8] > cb)
                                            if(p[offset12] > cb)
                                                if(p[offset13] > cb)
                                                    if(p[offset14] > cb)
                                                        if(p[offset15] > cb)
                                                        {}
                                                        else
                                                            if(p[offset6] > cb)
                                                                if(p[offset7] > cb)
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                    else
                                                        if(p[offset5] > cb)
                                                            if(p[offset6] > cb)
                                                                if(p[offset7] > cb)
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                else
                                                    if(p[offset4] > cb)
                                                        if(p[offset5] > cb)
                                                            if(p[offset6] > cb)
                                                                if(p[offset7] > cb)
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                            else
                                                if(p[offset3] > cb)
                                                    if(p[offset4] > cb)
                                                        if(p[offset5] > cb)
                                                            if(p[offset6] > cb)
                                                                if(p[offset7] > cb)
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                        else
                                            if(p[offset1] > cb)
                                                if(p[offset12] > cb)
                                                    if(p[offset13] > cb)
                                                        if(p[offset14] > cb)
                                                            if(p[offset15] > cb)
                                                            {}
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                    else
                                        continue;
                                else
                                    continue;
                            else if(p[offset9] < c_b)
                                if(p[offset7] < c_b)
                                    if(p[offset8] < c_b)
                                        if(p[offset6] < c_b)
                                            if(p[offset5] < c_b)
                                                if(p[offset4] < c_b)
                                                    if(p[offset3] < c_b)
                                                        if(p[offset1] < c_b)
                                                        {}
                                                        else
                                                            if(p[offset10] < c_b)
                                                            {}
                                                            else
                                                                continue;
                                                    else
                                                        if(p[offset10] < c_b)
                                                            if(p[offset11] < c_b)
                                                                if(p[offset12] < c_b)
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                else
                                                    if(p[offset10] < c_b)
                                                        if(p[offset11] < c_b)
                                                            if(p[offset12] < c_b)
                                                                if(p[offset13] < c_b)
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                            else
                                                if(p[offset10] < c_b)
                                                    if(p[offset11] < c_b)
                                                        if(p[offset12] < c_b)
                                                            if(p[offset13] < c_b)
                                                                if(p[offset14] < c_b)
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                        else
                                            if(p[offset10] < c_b)
                                                if(p[offset11] < c_b)
                                                    if(p[offset12] < c_b)
                                                        if(p[offset13] < c_b)
                                                            if(p[offset14] < c_b)
                                                                if(p[offset15] < c_b)
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                    else
                                        continue;
                                else
                                    continue;
                            else
                                continue;
                        else
                            if(p[offset9] > cb)
                                if(p[offset10] > cb)
                                    if(p[offset11] > cb)
                                        if(p[offset8] > cb)
                                            if(p[offset12] > cb)
                                                if(p[offset13] > cb)
                                                    if(p[offset14] > cb)
                                                        if(p[offset15] > cb)
                                                        {}
                                                        else
                                                            if(p[offset6] > cb)
                                                                if(p[offset7] > cb)
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                    else
                                                        if(p[offset5] > cb)
                                                            if(p[offset6] > cb)
                                                                if(p[offset7] > cb)
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                else
                                                    if(p[offset4] > cb)
                                                        if(p[offset5] > cb)
                                                            if(p[offset6] > cb)
                                                                if(p[offset7] > cb)
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                            else
                                                if(p[offset3] > cb)
                                                    if(p[offset4] > cb)
                                                        if(p[offset5] > cb)
                                                            if(p[offset6] > cb)
                                                                if(p[offset7] > cb)
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                        else
                                            if(p[offset1] > cb)
                                                if(p[offset12] > cb)
                                                    if(p[offset13] > cb)
                                                        if(p[offset14] > cb)
                                                            if(p[offset15] > cb)
                                                            {}
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                    else
                                        continue;
                                else
                                    continue;
                            else if(p[offset9] < c_b)
                                if(p[offset7] < c_b)
                                    if(p[offset8] < c_b)
                                        if(p[offset10] < c_b)
                                            if(p[offset11] < c_b)
                                                if(p[offset6] < c_b)
                                                    if(p[offset5] < c_b)
                                                        if(p[offset4] < c_b)
                                                            if(p[offset3] < c_b)
                                                            {}
                                                            else
                                                                if(p[offset12] < c_b)
                                                                {}
                                                                else
                                                                    continue;
                                                        else
                                                            if(p[offset12] < c_b)
                                                                if(p[offset13] < c_b)
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                    else
                                                        if(p[offset12] < c_b)
                                                            if(p[offset13] < c_b)
                                                                if(p[offset14] < c_b)
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                else
                                                    if(p[offset12] < c_b)
                                                        if(p[offset13] < c_b)
                                                            if(p[offset14] < c_b)
                                                                if(p[offset15] < c_b)
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                    else
                                        continue;
                                else
                                    continue;
                            else
                                continue;
                    else if(p[offset0] < c_b)
                        if(p[offset2] > cb)
                            if(p[offset9] > cb)
                                if(p[offset7] > cb)
                                    if(p[offset8] > cb)
                                        if(p[offset6] > cb)
                                            if(p[offset5] > cb)
                                                if(p[offset4] > cb)
                                                    if(p[offset3] > cb)
                                                        if(p[offset1] > cb)
                                                        {}
                                                        else
                                                            if(p[offset10] > cb)
                                                            {}
                                                            else
                                                                continue;
                                                    else
                                                        if(p[offset10] > cb)
                                                            if(p[offset11] > cb)
                                                                if(p[offset12] > cb)
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                else
                                                    if(p[offset10] > cb)
                                                        if(p[offset11] > cb)
                                                            if(p[offset12] > cb)
                                                                if(p[offset13] > cb)
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                            else
                                                if(p[offset10] > cb)
                                                    if(p[offset11] > cb)
                                                        if(p[offset12] > cb)
                                                            if(p[offset13] > cb)
                                                                if(p[offset14] > cb)
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                        else
                                            if(p[offset10] > cb)
                                                if(p[offset11] > cb)
                                                    if(p[offset12] > cb)
                                                        if(p[offset13] > cb)
                                                            if(p[offset14] > cb)
                                                                if(p[offset15] > cb)
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                    else
                                        continue;
                                else
                                    continue;
                            else if(p[offset9] < c_b)
                                if(p[offset10] < c_b)
                                    if(p[offset11] < c_b)
                                        if(p[offset8] < c_b)
                                            if(p[offset12] < c_b)
                                                if(p[offset13] < c_b)
                                                    if(p[offset14] < c_b)
                                                        if(p[offset15] < c_b)
                                                        {}
                                                        else
                                                            if(p[offset6] < c_b)
                                                                if(p[offset7] < c_b)
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                    else
                                                        if(p[offset5] < c_b)
                                                            if(p[offset6] < c_b)
                                                                if(p[offset7] < c_b)
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                else
                                                    if(p[offset4] < c_b)
                                                        if(p[offset5] < c_b)
                                                            if(p[offset6] < c_b)
                                                                if(p[offset7] < c_b)
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                            else
                                                if(p[offset3] < c_b)
                                                    if(p[offset4] < c_b)
                                                        if(p[offset5] < c_b)
                                                            if(p[offset6] < c_b)
                                                                if(p[offset7] < c_b)
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                        else
                                            if(p[offset1] < c_b)
                                                if(p[offset12] < c_b)
                                                    if(p[offset13] < c_b)
                                                        if(p[offset14] < c_b)
                                                            if(p[offset15] < c_b)
                                                            {}
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                    else
                                        continue;
                                else
                                    continue;
                            else
                                continue;
                        else if(p[offset2] < c_b)
                            if(p[offset4] > cb)
                                if(p[offset11] > cb)
                                    if(p[offset7] > cb)
                                        if(p[offset8] > cb)
                                            if(p[offset9] > cb)
                                                if(p[offset10] > cb)
                                                    if(p[offset6] > cb)
                                                        if(p[offset5] > cb)
                                                            if(p[offset3] > cb)
                                                            {}
                                                            else
                                                                if(p[offset12] > cb)
                                                                {}
                                                                else
                                                                    continue;
                                                        else
                                                            if(p[offset12] > cb)
                                                                if(p[offset13] > cb)
                                                                    if(p[offset14] > cb)
                                                                    {}
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                    else
                                                        if(p[offset12] > cb)
                                                            if(p[offset13] > cb)
                                                                if(p[offset14] > cb)
                                                                    if(p[offset15] > cb)
                                                                    {}
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                    else
                                        continue;
                                else if(p[offset11] < c_b)
                                    if(p[offset12] < c_b)
                                        if(p[offset13] < c_b)
                                            if(p[offset10] < c_b)
                                                if(p[offset14] < c_b)
                                                    if(p[offset15] < c_b)
                                                        if(p[offset1] < c_b)
                                                        {}
                                                        else
                                                            if(p[offset8] < c_b)
                                                                if(p[offset9] < c_b)
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                    else
                                                        if(p[offset6] < c_b)
                                                            if(p[offset7] < c_b)
                                                                if(p[offset8] < c_b)
                                                                    if(p[offset9] < c_b)
                                                                    {}
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                else
                                                    if(p[offset5] < c_b)
                                                        if(p[offset6] < c_b)
                                                            if(p[offset7] < c_b)
                                                                if(p[offset8] < c_b)
                                                                    if(p[offset9] < c_b)
                                                                    {}
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                            else
                                                if(p[offset1] < c_b)
                                                    if(p[offset3] < c_b)
                                                        if(p[offset14] < c_b)
                                                            if(p[offset15] < c_b)
                                                            {}
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                        else
                                            continue;
                                    else
                                        continue;
                                else
                                    continue;
                            else if(p[offset4] < c_b)
                                if(p[offset5] > cb)
                                    if(p[offset12] > cb)
                                        if(p[offset7] > cb)
                                            if(p[offset8] > cb)
                                                if(p[offset9] > cb)
                                                    if(p[offset10] > cb)
                                                        if(p[offset11] > cb)
                                                            if(p[offset13] > cb)
                                                                if(p[offset6] > cb)
                                                                {}
                                                                else
                                                                    if(p[offset14] > cb)
                                                                        if(p[offset15] > cb)
                                                                        {}
                                                                        else
                                                                            continue;
                                                                    else
                                                                        continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                    else if(p[offset12] < c_b)
                                        if(p[offset13] < c_b)
                                            if(p[offset14] < c_b)
                                                if(p[offset15] < c_b)
                                                    if(p[offset1] < c_b)
                                                        if(p[offset3] < c_b)
                                                        {}
                                                        else
                                                            if(p[offset10] < c_b)
                                                                if(p[offset11] < c_b)
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                    else
                                                        if(p[offset8] < c_b)
                                                            if(p[offset9] < c_b)
                                                                if(p[offset10] < c_b)
                                                                    if(p[offset11] < c_b)
                                                                    {}
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                else
                                                    if(p[offset6] < c_b)
                                                        if(p[offset7] < c_b)
                                                            if(p[offset8] < c_b)
                                                                if(p[offset9] < c_b)
                                                                    if(p[offset10] < c_b)
                                                                        if(p[offset11] < c_b)
                                                                        {}
                                                                        else
                                                                            continue;
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                    else
                                        continue;
                                else if(p[offset5] < c_b)
                                    if(p[offset7] > cb)
                                        if(p[offset14] > cb)
                                            if(p[offset8] > cb)
                                                if(p[offset9] > cb)
                                                    if(p[offset10] > cb)
                                                        if(p[offset11] > cb)
                                                            if(p[offset12] > cb)
                                                                if(p[offset13] > cb)
                                                                    if(p[offset6] > cb)
                                                                    {}
                                                                    else
                                                                        if(p[offset15] > cb)
                                                                        {}
                                                                        else
                                                                            continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else if(p[offset14] < c_b)
                                            if(p[offset15] < c_b)
                                                if(p[offset1] < c_b)
                                                    if(p[offset3] < c_b)
                                                        if(p[offset6] < c_b)
                                                        {}
                                                        else
                                                            if(p[offset13] < c_b)
                                                            {}
                                                            else
                                                                continue;
                                                    else
                                                        if(p[offset10] < c_b)
                                                            if(p[offset11] < c_b)
                                                                if(p[offset12] < c_b)
                                                                    if(p[offset13] < c_b)
                                                                    {}
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                else
                                                    if(p[offset8] < c_b)
                                                        if(p[offset9] < c_b)
                                                            if(p[offset10] < c_b)
                                                                if(p[offset11] < c_b)
                                                                    if(p[offset12] < c_b)
                                                                        if(p[offset13] < c_b)
                                                                        {}
                                                                        else
                                                                            continue;
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                    else if(p[offset7] < c_b)
                                        if(p[offset3] < c_b)
                                            if(p[offset1] < c_b)
                                                if(p[offset6] < c_b)
                                                    if(p[offset8] < c_b)
                                                    {}
                                                    else
                                                        if(p[offset15] < c_b)
                                                        {}
                                                        else
                                                            continue;
                                                else
                                                    if(p[offset13] < c_b)
                                                        if(p[offset14] < c_b)
                                                            if(p[offset15] < c_b)
                                                            {}
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                            else
                                                if(p[offset8] < c_b)
                                                    if(p[offset9] < c_b)
                                                        if(p[offset10] < c_b)
                                                            if(p[offset6] < c_b)
                                                            {}
                                                            else
                                                                if(p[offset11] < c_b)
                                                                    if(p[offset12] < c_b)
                                                                        if(p[offset13] < c_b)
                                                                            if(p[offset14] < c_b)
                                                                                if(p[offset15] < c_b)
                                                                                {}
                                                                                else
                                                                                    continue;
                                                                            else
                                                                                continue;
                                                                        else
                                                                            continue;
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                        else
                                            if(p[offset10] < c_b)
                                                if(p[offset11] < c_b)
                                                    if(p[offset12] < c_b)
                                                        if(p[offset8] < c_b)
                                                            if(p[offset9] < c_b)
                                                                if(p[offset6] < c_b)
                                                                {}
                                                                else
                                                                    if(p[offset13] < c_b)
                                                                        if(p[offset14] < c_b)
                                                                            if(p[offset15] < c_b)
                                                                            {}
                                                                            else
                                                                                continue;
                                                                        else
                                                                            continue;
                                                                    else
                                                                        continue;
                                                            else
                                                                if(p[offset1] < c_b)
                                                                    if(p[offset13] < c_b)
                                                                        if(p[offset14] < c_b)
                                                                            if(p[offset15] < c_b)
                                                                            {}
                                                                            else
                                                                                continue;
                                                                        else
                                                                            continue;
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                        else
                                                            if(p[offset1] < c_b)
                                                                if(p[offset13] < c_b)
                                                                    if(p[offset14] < c_b)
                                                                        if(p[offset15] < c_b)
                                                                        {}
                                                                        else
                                                                            continue;
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                    else
                                        if(p[offset14] < c_b)
                                            if(p[offset15] < c_b)
                                                if(p[offset1] < c_b)
                                                    if(p[offset3] < c_b)
                                                        if(p[offset6] < c_b)
                                                        {}
                                                        else
                                                            if(p[offset13] < c_b)
                                                            {}
                                                            else
                                                                continue;
                                                    else
                                                        if(p[offset10] < c_b)
                                                            if(p[offset11] < c_b)
                                                                if(p[offset12] < c_b)
                                                                    if(p[offset13] < c_b)
                                                                    {}
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                else
                                                    if(p[offset8] < c_b)
                                                        if(p[offset9] < c_b)
                                                            if(p[offset10] < c_b)
                                                                if(p[offset11] < c_b)
                                                                    if(p[offset12] < c_b)
                                                                        if(p[offset13] < c_b)
                                                                        {}
                                                                        else
                                                                            continue;
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                else
                                    if(p[offset12] > cb)
                                        if(p[offset7] > cb)
                                            if(p[offset8] > cb)
                                                if(p[offset9] > cb)
                                                    if(p[offset10] > cb)
                                                        if(p[offset11] > cb)
                                                            if(p[offset13] > cb)
                                                                if(p[offset14] > cb)
                                                                    if(p[offset6] > cb)
                                                                    {}
                                                                    else
                                                                        if(p[offset15] > cb)
                                                                        {}
                                                                        else
                                                                            continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                    else if(p[offset12] < c_b)
                                        if(p[offset13] < c_b)
                                            if(p[offset14] < c_b)
                                                if(p[offset15] < c_b)
                                                    if(p[offset1] < c_b)
                                                        if(p[offset3] < c_b)
                                                        {}
                                                        else
                                                            if(p[offset10] < c_b)
                                                                if(p[offset11] < c_b)
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                    else
                                                        if(p[offset8] < c_b)
                                                            if(p[offset9] < c_b)
                                                                if(p[offset10] < c_b)
                                                                    if(p[offset11] < c_b)
                                                                    {}
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                else
                                                    if(p[offset6] < c_b)
                                                        if(p[offset7] < c_b)
                                                            if(p[offset8] < c_b)
                                                                if(p[offset9] < c_b)
                                                                    if(p[offset10] < c_b)
                                                                        if(p[offset11] < c_b)
                                                                        {}
                                                                        else
                                                                            continue;
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                    else
                                        continue;
                            else
                                if(p[offset11] > cb)
                                    if(p[offset7] > cb)
                                        if(p[offset8] > cb)
                                            if(p[offset9] > cb)
                                                if(p[offset10] > cb)
                                                    if(p[offset12] > cb)
                                                        if(p[offset13] > cb)
                                                            if(p[offset6] > cb)
                                                                if(p[offset5] > cb)
                                                                {}
                                                                else
                                                                    if(p[offset14] > cb)
                                                                    {}
                                                                    else
                                                                        continue;
                                                            else
                                                                if(p[offset14] > cb)
                                                                    if(p[offset15] > cb)
                                                                    {}
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                    else
                                        continue;
                                else if(p[offset11] < c_b)
                                    if(p[offset12] < c_b)
                                        if(p[offset13] < c_b)
                                            if(p[offset10] < c_b)
                                                if(p[offset14] < c_b)
                                                    if(p[offset15] < c_b)
                                                        if(p[offset1] < c_b)
                                                        {}
                                                        else
                                                            if(p[offset8] < c_b)
                                                                if(p[offset9] < c_b)
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                    else
                                                        if(p[offset6] < c_b)
                                                            if(p[offset7] < c_b)
                                                                if(p[offset8] < c_b)
                                                                    if(p[offset9] < c_b)
                                                                    {}
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                else
                                                    if(p[offset5] < c_b)
                                                        if(p[offset6] < c_b)
                                                            if(p[offset7] < c_b)
                                                                if(p[offset8] < c_b)
                                                                    if(p[offset9] < c_b)
                                                                    {}
                                                                    else
                                                                        continue;
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                            else
                                                if(p[offset1] < c_b)
                                                    if(p[offset3] < c_b)
                                                        if(p[offset14] < c_b)
                                                            if(p[offset15] < c_b)
                                                            {}
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                        else
                                            continue;
                                    else
                                        continue;
                                else
                                    continue;
                        else
                            if(p[offset9] > cb)
                                if(p[offset7] > cb)
                                    if(p[offset8] > cb)
                                        if(p[offset10] > cb)
                                            if(p[offset11] > cb)
                                                if(p[offset6] > cb)
                                                    if(p[offset5] > cb)
                                                        if(p[offset4] > cb)
                                                            if(p[offset3] > cb)
                                                            {}
                                                            else
                                                                if(p[offset12] > cb)
                                                                {}
                                                                else
                                                                    continue;
                                                        else
                                                            if(p[offset12] > cb)
                                                                if(p[offset13] > cb)
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                    else
                                                        if(p[offset12] > cb)
                                                            if(p[offset13] > cb)
                                                                if(p[offset14] > cb)
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                else
                                                    if(p[offset12] > cb)
                                                        if(p[offset13] > cb)
                                                            if(p[offset14] > cb)
                                                                if(p[offset15] > cb)
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                    else
                                        continue;
                                else
                                    continue;
                            else if(p[offset9] < c_b)
                                if(p[offset10] < c_b)
                                    if(p[offset11] < c_b)
                                        if(p[offset8] < c_b)
                                            if(p[offset12] < c_b)
                                                if(p[offset13] < c_b)
                                                    if(p[offset14] < c_b)
                                                        if(p[offset15] < c_b)
                                                        {}
                                                        else
                                                            if(p[offset6] < c_b)
                                                                if(p[offset7] < c_b)
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                    else
                                                        if(p[offset5] < c_b)
                                                            if(p[offset6] < c_b)
                                                                if(p[offset7] < c_b)
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                else
                                                    if(p[offset4] < c_b)
                                                        if(p[offset5] < c_b)
                                                            if(p[offset6] < c_b)
                                                                if(p[offset7] < c_b)
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                            else
                                                if(p[offset3] < c_b)
                                                    if(p[offset4] < c_b)
                                                        if(p[offset5] < c_b)
                                                            if(p[offset6] < c_b)
                                                                if(p[offset7] < c_b)
                                                                {}
                                                                else
                                                                    continue;
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                        else
                                            if(p[offset1] < c_b)
                                                if(p[offset12] < c_b)
                                                    if(p[offset13] < c_b)
                                                        if(p[offset14] < c_b)
                                                            if(p[offset15] < c_b)
                                                            {}
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                    else
                                        continue;
                                else
                                    continue;
                            else
                                continue;
                    else
                        if(p[offset7] > cb)
                            if(p[offset8] > cb)
                                if(p[offset9] > cb)
                                    if(p[offset6] > cb)
                                        if(p[offset5] > cb)
                                            if(p[offset4] > cb)
                                                if(p[offset3] > cb)
                                                    if(p[offset2] > cb)
                                                        if(p[offset1] > cb)
                                                        {}
                                                        else
                                                            if(p[offset10] > cb)
                                                            {}
                                                            else
                                                                continue;
                                                    else
                                                        if(p[offset10] > cb)
                                                            if(p[offset11] > cb)
                                                            {}
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                else
                                                    if(p[offset10] > cb)
                                                        if(p[offset11] > cb)
                                                            if(p[offset12] > cb)
                                                            {}
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                            else
                                                if(p[offset10] > cb)
                                                    if(p[offset11] > cb)
                                                        if(p[offset12] > cb)
                                                            if(p[offset13] > cb)
                                                            {}
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                        else
                                            if(p[offset10] > cb)
                                                if(p[offset11] > cb)
                                                    if(p[offset12] > cb)
                                                        if(p[offset13] > cb)
                                                            if(p[offset14] > cb)
                                                            {}
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                    else
                                        if(p[offset10] > cb)
                                            if(p[offset11] > cb)
                                                if(p[offset12] > cb)
                                                    if(p[offset13] > cb)
                                                        if(p[offset14] > cb)
                                                            if(p[offset15] > cb)
                                                            {}
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                else
                                    continue;
                            else
                                continue;
                        else if(p[offset7] < c_b)
                            if(p[offset8] < c_b)
                                if(p[offset9] < c_b)
                                    if(p[offset6] < c_b)
                                        if(p[offset5] < c_b)
                                            if(p[offset4] < c_b)
                                                if(p[offset3] < c_b)
                                                    if(p[offset2] < c_b)
                                                        if(p[offset1] < c_b)
                                                        {}
                                                        else
                                                            if(p[offset10] < c_b)
                                                            {}
                                                            else
                                                                continue;
                                                    else
                                                        if(p[offset10] < c_b)
                                                            if(p[offset11] < c_b)
                                                            {}
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                else
                                                    if(p[offset10] < c_b)
                                                        if(p[offset11] < c_b)
                                                            if(p[offset12] < c_b)
                                                            {}
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                            else
                                                if(p[offset10] < c_b)
                                                    if(p[offset11] < c_b)
                                                        if(p[offset12] < c_b)
                                                            if(p[offset13] < c_b)
                                                            {}
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                        else
                                            if(p[offset10] < c_b)
                                                if(p[offset11] < c_b)
                                                    if(p[offset12] < c_b)
                                                        if(p[offset13] < c_b)
                                                            if(p[offset14] < c_b)
                                                            {}
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                    else
                                        if(p[offset10] < c_b)
                                            if(p[offset11] < c_b)
                                                if(p[offset12] < c_b)
                                                    if(p[offset13] < c_b)
                                                        if(p[offset14] < c_b)
                                                            if(p[offset15] < c_b)
                                                            {}
                                                            else
                                                                continue;
                                                        else
                                                            continue;
                                                    else
                                                        continue;
                                                else
                                                    continue;
                                            else
                                                continue;
                                        else
                                            continue;
                                else
                                    continue;
                            else
                                continue;
                        else
                            continue;
                }
                features( x, y, cornerScore( im + y * map.stride() + x, threshold ) );
            }
        }
    }

    int OAST9_16::cornerScore(const uint8_t* p, uint8_t thresh ) const
    {
        int bmin = thresh;
        int bmax = 255;
        int b_test = (bmax + bmin)/2;

        while(1)
        {
            register const int cb = *p + b_test;
            register const int c_b = *p - b_test;
            if(p[offset0] > cb)
                if(p[offset2] > cb)
                    if(p[offset4] > cb)
                        if(p[offset5] > cb)
                            if(p[offset7] > cb)
                                if(p[offset3] > cb)
                                    if(p[offset1] > cb)
                                        if(p[offset6] > cb)
                                            if(p[offset8] > cb)
                                                goto is_a_corner;
                                            else
                                                if(p[offset15] > cb)
                                                    goto is_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            if(p[offset13] > cb)
                                                if(p[offset14] > cb)
                                                    if(p[offset15] > cb)
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                    else
                                        if(p[offset8] > cb)
                                            if(p[offset9] > cb)
                                                if(p[offset10] > cb)
                                                    if(p[offset6] > cb)
                                                        goto is_a_corner;
                                                    else
                                                        if(p[offset11] > cb)
                                                            if(p[offset12] > cb)
                                                                if(p[offset13] > cb)
                                                                    if(p[offset14] > cb)
                                                                        if(p[offset15] > cb)
                                                                            goto is_a_corner;
                                                                        else
                                                                            goto is_not_a_corner;
                                                                    else
                                                                        goto is_not_a_corner;
                                                                else
                                                                    goto is_not_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                else
                                    if(p[offset10] > cb)
                                        if(p[offset11] > cb)
                                            if(p[offset12] > cb)
                                                if(p[offset8] > cb)
                                                    if(p[offset9] > cb)
                                                        if(p[offset6] > cb)
                                                            goto is_a_corner;
                                                        else
                                                            if(p[offset13] > cb)
                                                                if(p[offset14] > cb)
                                                                    if(p[offset15] > cb)
                                                                        goto is_a_corner;
                                                                    else
                                                                        goto is_not_a_corner;
                                                                else
                                                                    goto is_not_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                    else
                                                        if(p[offset1] > cb)
                                                            if(p[offset13] > cb)
                                                                if(p[offset14] > cb)
                                                                    if(p[offset15] > cb)
                                                                        goto is_a_corner;
                                                                    else
                                                                        goto is_not_a_corner;
                                                                else
                                                                    goto is_not_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                else
                                                    if(p[offset1] > cb)
                                                        if(p[offset13] > cb)
                                                            if(p[offset14] > cb)
                                                                if(p[offset15] > cb)
                                                                    goto is_a_corner;
                                                                else
                                                                    goto is_not_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                            else if(p[offset7] < c_b)
                                if(p[offset14] > cb)
                                    if(p[offset15] > cb)
                                        if(p[offset1] > cb)
                                            if(p[offset3] > cb)
                                                if(p[offset6] > cb)
                                                    goto is_a_corner;
                                                else
                                                    if(p[offset13] > cb)
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                            else
                                                if(p[offset10] > cb)
                                                    if(p[offset11] > cb)
                                                        if(p[offset12] > cb)
                                                            if(p[offset13] > cb)
                                                                goto is_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            if(p[offset8] > cb)
                                                if(p[offset9] > cb)
                                                    if(p[offset10] > cb)
                                                        if(p[offset11] > cb)
                                                            if(p[offset12] > cb)
                                                                if(p[offset13] > cb)
                                                                    goto is_a_corner;
                                                                else
                                                                    goto is_not_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else if(p[offset14] < c_b)
                                    if(p[offset8] < c_b)
                                        if(p[offset9] < c_b)
                                            if(p[offset10] < c_b)
                                                if(p[offset11] < c_b)
                                                    if(p[offset12] < c_b)
                                                        if(p[offset13] < c_b)
                                                            if(p[offset6] < c_b)
                                                                goto is_a_corner;
                                                            else
                                                                if(p[offset15] < c_b)
                                                                    goto is_a_corner;
                                                                else
                                                                    goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                            else
                                if(p[offset14] > cb)
                                    if(p[offset15] > cb)
                                        if(p[offset1] > cb)
                                            if(p[offset3] > cb)
                                                if(p[offset6] > cb)
                                                    goto is_a_corner;
                                                else
                                                    if(p[offset13] > cb)
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                            else
                                                if(p[offset10] > cb)
                                                    if(p[offset11] > cb)
                                                        if(p[offset12] > cb)
                                                            if(p[offset13] > cb)
                                                                goto is_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            if(p[offset8] > cb)
                                                if(p[offset9] > cb)
                                                    if(p[offset10] > cb)
                                                        if(p[offset11] > cb)
                                                            if(p[offset12] > cb)
                                                                if(p[offset13] > cb)
                                                                    goto is_a_corner;
                                                                else
                                                                    goto is_not_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                        else if(p[offset5] < c_b)
                            if(p[offset12] > cb)
                                if(p[offset13] > cb)
                                    if(p[offset14] > cb)
                                        if(p[offset15] > cb)
                                            if(p[offset1] > cb)
                                                if(p[offset3] > cb)
                                                    goto is_a_corner;
                                                else
                                                    if(p[offset10] > cb)
                                                        if(p[offset11] > cb)
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                            else
                                                if(p[offset8] > cb)
                                                    if(p[offset9] > cb)
                                                        if(p[offset10] > cb)
                                                            if(p[offset11] > cb)
                                                                goto is_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            if(p[offset6] > cb)
                                                if(p[offset7] > cb)
                                                    if(p[offset8] > cb)
                                                        if(p[offset9] > cb)
                                                            if(p[offset10] > cb)
                                                                if(p[offset11] > cb)
                                                                    goto is_a_corner;
                                                                else
                                                                    goto is_not_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                            else if(p[offset12] < c_b)
                                if(p[offset7] < c_b)
                                    if(p[offset8] < c_b)
                                        if(p[offset9] < c_b)
                                            if(p[offset10] < c_b)
                                                if(p[offset11] < c_b)
                                                    if(p[offset13] < c_b)
                                                        if(p[offset6] < c_b)
                                                            goto is_a_corner;
                                                        else
                                                            if(p[offset14] < c_b)
                                                                if(p[offset15] < c_b)
                                                                    goto is_a_corner;
                                                                else
                                                                    goto is_not_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                            else
                                goto is_not_a_corner;
                        else
                            if(p[offset12] > cb)
                                if(p[offset13] > cb)
                                    if(p[offset14] > cb)
                                        if(p[offset15] > cb)
                                            if(p[offset1] > cb)
                                                if(p[offset3] > cb)
                                                    goto is_a_corner;
                                                else
                                                    if(p[offset10] > cb)
                                                        if(p[offset11] > cb)
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                            else
                                                if(p[offset8] > cb)
                                                    if(p[offset9] > cb)
                                                        if(p[offset10] > cb)
                                                            if(p[offset11] > cb)
                                                                goto is_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            if(p[offset6] > cb)
                                                if(p[offset7] > cb)
                                                    if(p[offset8] > cb)
                                                        if(p[offset9] > cb)
                                                            if(p[offset10] > cb)
                                                                if(p[offset11] > cb)
                                                                    goto is_a_corner;
                                                                else
                                                                    goto is_not_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                            else if(p[offset12] < c_b)
                                if(p[offset7] < c_b)
                                    if(p[offset8] < c_b)
                                        if(p[offset9] < c_b)
                                            if(p[offset10] < c_b)
                                                if(p[offset11] < c_b)
                                                    if(p[offset13] < c_b)
                                                        if(p[offset14] < c_b)
                                                            if(p[offset6] < c_b)
                                                                goto is_a_corner;
                                                            else
                                                                if(p[offset15] < c_b)
                                                                    goto is_a_corner;
                                                                else
                                                                    goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                            else
                                goto is_not_a_corner;
                    else if(p[offset4] < c_b)
                        if(p[offset11] > cb)
                            if(p[offset12] > cb)
                                if(p[offset13] > cb)
                                    if(p[offset10] > cb)
                                        if(p[offset14] > cb)
                                            if(p[offset15] > cb)
                                                if(p[offset1] > cb)
                                                    goto is_a_corner;
                                                else
                                                    if(p[offset8] > cb)
                                                        if(p[offset9] > cb)
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                            else
                                                if(p[offset6] > cb)
                                                    if(p[offset7] > cb)
                                                        if(p[offset8] > cb)
                                                            if(p[offset9] > cb)
                                                                goto is_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            if(p[offset5] > cb)
                                                if(p[offset6] > cb)
                                                    if(p[offset7] > cb)
                                                        if(p[offset8] > cb)
                                                            if(p[offset9] > cb)
                                                                goto is_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                    else
                                        if(p[offset1] > cb)
                                            if(p[offset3] > cb)
                                                if(p[offset14] > cb)
                                                    if(p[offset15] > cb)
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                            else
                                goto is_not_a_corner;
                        else if(p[offset11] < c_b)
                            if(p[offset7] < c_b)
                                if(p[offset8] < c_b)
                                    if(p[offset9] < c_b)
                                        if(p[offset10] < c_b)
                                            if(p[offset6] < c_b)
                                                if(p[offset5] < c_b)
                                                    if(p[offset3] < c_b)
                                                        goto is_a_corner;
                                                    else
                                                        if(p[offset12] < c_b)
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                else
                                                    if(p[offset12] < c_b)
                                                        if(p[offset13] < c_b)
                                                            if(p[offset14] < c_b)
                                                                goto is_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                            else
                                                if(p[offset12] < c_b)
                                                    if(p[offset13] < c_b)
                                                        if(p[offset14] < c_b)
                                                            if(p[offset15] < c_b)
                                                                goto is_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                            else
                                goto is_not_a_corner;
                        else
                            goto is_not_a_corner;
                    else
                        if(p[offset11] > cb)
                            if(p[offset12] > cb)
                                if(p[offset13] > cb)
                                    if(p[offset10] > cb)
                                        if(p[offset14] > cb)
                                            if(p[offset15] > cb)
                                                if(p[offset1] > cb)
                                                    goto is_a_corner;
                                                else
                                                    if(p[offset8] > cb)
                                                        if(p[offset9] > cb)
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                            else
                                                if(p[offset6] > cb)
                                                    if(p[offset7] > cb)
                                                        if(p[offset8] > cb)
                                                            if(p[offset9] > cb)
                                                                goto is_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            if(p[offset5] > cb)
                                                if(p[offset6] > cb)
                                                    if(p[offset7] > cb)
                                                        if(p[offset8] > cb)
                                                            if(p[offset9] > cb)
                                                                goto is_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                    else
                                        if(p[offset1] > cb)
                                            if(p[offset3] > cb)
                                                if(p[offset14] > cb)
                                                    if(p[offset15] > cb)
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                            else
                                goto is_not_a_corner;
                        else if(p[offset11] < c_b)
                            if(p[offset7] < c_b)
                                if(p[offset8] < c_b)
                                    if(p[offset9] < c_b)
                                        if(p[offset10] < c_b)
                                            if(p[offset12] < c_b)
                                                if(p[offset13] < c_b)
                                                    if(p[offset6] < c_b)
                                                        if(p[offset5] < c_b)
                                                            goto is_a_corner;
                                                        else
                                                            if(p[offset14] < c_b)
                                                                goto is_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                    else
                                                        if(p[offset14] < c_b)
                                                            if(p[offset15] < c_b)
                                                                goto is_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                            else
                                goto is_not_a_corner;
                        else
                            goto is_not_a_corner;
                else if(p[offset2] < c_b)
                    if(p[offset9] > cb)
                        if(p[offset10] > cb)
                            if(p[offset11] > cb)
                                if(p[offset8] > cb)
                                    if(p[offset12] > cb)
                                        if(p[offset13] > cb)
                                            if(p[offset14] > cb)
                                                if(p[offset15] > cb)
                                                    goto is_a_corner;
                                                else
                                                    if(p[offset6] > cb)
                                                        if(p[offset7] > cb)
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                            else
                                                if(p[offset5] > cb)
                                                    if(p[offset6] > cb)
                                                        if(p[offset7] > cb)
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            if(p[offset4] > cb)
                                                if(p[offset5] > cb)
                                                    if(p[offset6] > cb)
                                                        if(p[offset7] > cb)
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                    else
                                        if(p[offset3] > cb)
                                            if(p[offset4] > cb)
                                                if(p[offset5] > cb)
                                                    if(p[offset6] > cb)
                                                        if(p[offset7] > cb)
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                else
                                    if(p[offset1] > cb)
                                        if(p[offset12] > cb)
                                            if(p[offset13] > cb)
                                                if(p[offset14] > cb)
                                                    if(p[offset15] > cb)
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                            else
                                goto is_not_a_corner;
                        else
                            goto is_not_a_corner;
                    else if(p[offset9] < c_b)
                        if(p[offset7] < c_b)
                            if(p[offset8] < c_b)
                                if(p[offset6] < c_b)
                                    if(p[offset5] < c_b)
                                        if(p[offset4] < c_b)
                                            if(p[offset3] < c_b)
                                                if(p[offset1] < c_b)
                                                    goto is_a_corner;
                                                else
                                                    if(p[offset10] < c_b)
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                            else
                                                if(p[offset10] < c_b)
                                                    if(p[offset11] < c_b)
                                                        if(p[offset12] < c_b)
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            if(p[offset10] < c_b)
                                                if(p[offset11] < c_b)
                                                    if(p[offset12] < c_b)
                                                        if(p[offset13] < c_b)
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                    else
                                        if(p[offset10] < c_b)
                                            if(p[offset11] < c_b)
                                                if(p[offset12] < c_b)
                                                    if(p[offset13] < c_b)
                                                        if(p[offset14] < c_b)
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                else
                                    if(p[offset10] < c_b)
                                        if(p[offset11] < c_b)
                                            if(p[offset12] < c_b)
                                                if(p[offset13] < c_b)
                                                    if(p[offset14] < c_b)
                                                        if(p[offset15] < c_b)
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                            else
                                goto is_not_a_corner;
                        else
                            goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                else
                    if(p[offset9] > cb)
                        if(p[offset10] > cb)
                            if(p[offset11] > cb)
                                if(p[offset8] > cb)
                                    if(p[offset12] > cb)
                                        if(p[offset13] > cb)
                                            if(p[offset14] > cb)
                                                if(p[offset15] > cb)
                                                    goto is_a_corner;
                                                else
                                                    if(p[offset6] > cb)
                                                        if(p[offset7] > cb)
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                            else
                                                if(p[offset5] > cb)
                                                    if(p[offset6] > cb)
                                                        if(p[offset7] > cb)
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            if(p[offset4] > cb)
                                                if(p[offset5] > cb)
                                                    if(p[offset6] > cb)
                                                        if(p[offset7] > cb)
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                    else
                                        if(p[offset3] > cb)
                                            if(p[offset4] > cb)
                                                if(p[offset5] > cb)
                                                    if(p[offset6] > cb)
                                                        if(p[offset7] > cb)
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                else
                                    if(p[offset1] > cb)
                                        if(p[offset12] > cb)
                                            if(p[offset13] > cb)
                                                if(p[offset14] > cb)
                                                    if(p[offset15] > cb)
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                            else
                                goto is_not_a_corner;
                        else
                            goto is_not_a_corner;
                    else if(p[offset9] < c_b)
                        if(p[offset7] < c_b)
                            if(p[offset8] < c_b)
                                if(p[offset10] < c_b)
                                    if(p[offset11] < c_b)
                                        if(p[offset6] < c_b)
                                            if(p[offset5] < c_b)
                                                if(p[offset4] < c_b)
                                                    if(p[offset3] < c_b)
                                                        goto is_a_corner;
                                                    else
                                                        if(p[offset12] < c_b)
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                else
                                                    if(p[offset12] < c_b)
                                                        if(p[offset13] < c_b)
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                            else
                                                if(p[offset12] < c_b)
                                                    if(p[offset13] < c_b)
                                                        if(p[offset14] < c_b)
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            if(p[offset12] < c_b)
                                                if(p[offset13] < c_b)
                                                    if(p[offset14] < c_b)
                                                        if(p[offset15] < c_b)
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                            else
                                goto is_not_a_corner;
                        else
                            goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
            else if(p[offset0] < c_b)
                if(p[offset2] > cb)
                    if(p[offset9] > cb)
                        if(p[offset7] > cb)
                            if(p[offset8] > cb)
                                if(p[offset6] > cb)
                                    if(p[offset5] > cb)
                                        if(p[offset4] > cb)
                                            if(p[offset3] > cb)
                                                if(p[offset1] > cb)
                                                    goto is_a_corner;
                                                else
                                                    if(p[offset10] > cb)
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                            else
                                                if(p[offset10] > cb)
                                                    if(p[offset11] > cb)
                                                        if(p[offset12] > cb)
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            if(p[offset10] > cb)
                                                if(p[offset11] > cb)
                                                    if(p[offset12] > cb)
                                                        if(p[offset13] > cb)
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                    else
                                        if(p[offset10] > cb)
                                            if(p[offset11] > cb)
                                                if(p[offset12] > cb)
                                                    if(p[offset13] > cb)
                                                        if(p[offset14] > cb)
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                else
                                    if(p[offset10] > cb)
                                        if(p[offset11] > cb)
                                            if(p[offset12] > cb)
                                                if(p[offset13] > cb)
                                                    if(p[offset14] > cb)
                                                        if(p[offset15] > cb)
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                            else
                                goto is_not_a_corner;
                        else
                            goto is_not_a_corner;
                    else if(p[offset9] < c_b)
                        if(p[offset10] < c_b)
                            if(p[offset11] < c_b)
                                if(p[offset8] < c_b)
                                    if(p[offset12] < c_b)
                                        if(p[offset13] < c_b)
                                            if(p[offset14] < c_b)
                                                if(p[offset15] < c_b)
                                                    goto is_a_corner;
                                                else
                                                    if(p[offset6] < c_b)
                                                        if(p[offset7] < c_b)
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                            else
                                                if(p[offset5] < c_b)
                                                    if(p[offset6] < c_b)
                                                        if(p[offset7] < c_b)
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            if(p[offset4] < c_b)
                                                if(p[offset5] < c_b)
                                                    if(p[offset6] < c_b)
                                                        if(p[offset7] < c_b)
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                    else
                                        if(p[offset3] < c_b)
                                            if(p[offset4] < c_b)
                                                if(p[offset5] < c_b)
                                                    if(p[offset6] < c_b)
                                                        if(p[offset7] < c_b)
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                else
                                    if(p[offset1] < c_b)
                                        if(p[offset12] < c_b)
                                            if(p[offset13] < c_b)
                                                if(p[offset14] < c_b)
                                                    if(p[offset15] < c_b)
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                            else
                                goto is_not_a_corner;
                        else
                            goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                else if(p[offset2] < c_b)
                    if(p[offset4] > cb)
                        if(p[offset11] > cb)
                            if(p[offset7] > cb)
                                if(p[offset8] > cb)
                                    if(p[offset9] > cb)
                                        if(p[offset10] > cb)
                                            if(p[offset6] > cb)
                                                if(p[offset5] > cb)
                                                    if(p[offset3] > cb)
                                                        goto is_a_corner;
                                                    else
                                                        if(p[offset12] > cb)
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                else
                                                    if(p[offset12] > cb)
                                                        if(p[offset13] > cb)
                                                            if(p[offset14] > cb)
                                                                goto is_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                            else
                                                if(p[offset12] > cb)
                                                    if(p[offset13] > cb)
                                                        if(p[offset14] > cb)
                                                            if(p[offset15] > cb)
                                                                goto is_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                            else
                                goto is_not_a_corner;
                        else if(p[offset11] < c_b)
                            if(p[offset12] < c_b)
                                if(p[offset13] < c_b)
                                    if(p[offset10] < c_b)
                                        if(p[offset14] < c_b)
                                            if(p[offset15] < c_b)
                                                if(p[offset1] < c_b)
                                                    goto is_a_corner;
                                                else
                                                    if(p[offset8] < c_b)
                                                        if(p[offset9] < c_b)
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                            else
                                                if(p[offset6] < c_b)
                                                    if(p[offset7] < c_b)
                                                        if(p[offset8] < c_b)
                                                            if(p[offset9] < c_b)
                                                                goto is_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            if(p[offset5] < c_b)
                                                if(p[offset6] < c_b)
                                                    if(p[offset7] < c_b)
                                                        if(p[offset8] < c_b)
                                                            if(p[offset9] < c_b)
                                                                goto is_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                    else
                                        if(p[offset1] < c_b)
                                            if(p[offset3] < c_b)
                                                if(p[offset14] < c_b)
                                                    if(p[offset15] < c_b)
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                            else
                                goto is_not_a_corner;
                        else
                            goto is_not_a_corner;
                    else if(p[offset4] < c_b)
                        if(p[offset5] > cb)
                            if(p[offset12] > cb)
                                if(p[offset7] > cb)
                                    if(p[offset8] > cb)
                                        if(p[offset9] > cb)
                                            if(p[offset10] > cb)
                                                if(p[offset11] > cb)
                                                    if(p[offset13] > cb)
                                                        if(p[offset6] > cb)
                                                            goto is_a_corner;
                                                        else
                                                            if(p[offset14] > cb)
                                                                if(p[offset15] > cb)
                                                                    goto is_a_corner;
                                                                else
                                                                    goto is_not_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                            else if(p[offset12] < c_b)
                                if(p[offset13] < c_b)
                                    if(p[offset14] < c_b)
                                        if(p[offset15] < c_b)
                                            if(p[offset1] < c_b)
                                                if(p[offset3] < c_b)
                                                    goto is_a_corner;
                                                else
                                                    if(p[offset10] < c_b)
                                                        if(p[offset11] < c_b)
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                            else
                                                if(p[offset8] < c_b)
                                                    if(p[offset9] < c_b)
                                                        if(p[offset10] < c_b)
                                                            if(p[offset11] < c_b)
                                                                goto is_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            if(p[offset6] < c_b)
                                                if(p[offset7] < c_b)
                                                    if(p[offset8] < c_b)
                                                        if(p[offset9] < c_b)
                                                            if(p[offset10] < c_b)
                                                                if(p[offset11] < c_b)
                                                                    goto is_a_corner;
                                                                else
                                                                    goto is_not_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                            else
                                goto is_not_a_corner;
                        else if(p[offset5] < c_b)
                            if(p[offset7] > cb)
                                if(p[offset14] > cb)
                                    if(p[offset8] > cb)
                                        if(p[offset9] > cb)
                                            if(p[offset10] > cb)
                                                if(p[offset11] > cb)
                                                    if(p[offset12] > cb)
                                                        if(p[offset13] > cb)
                                                            if(p[offset6] > cb)
                                                                goto is_a_corner;
                                                            else
                                                                if(p[offset15] > cb)
                                                                    goto is_a_corner;
                                                                else
                                                                    goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else if(p[offset14] < c_b)
                                    if(p[offset15] < c_b)
                                        if(p[offset1] < c_b)
                                            if(p[offset3] < c_b)
                                                if(p[offset6] < c_b)
                                                    goto is_a_corner;
                                                else
                                                    if(p[offset13] < c_b)
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                            else
                                                if(p[offset10] < c_b)
                                                    if(p[offset11] < c_b)
                                                        if(p[offset12] < c_b)
                                                            if(p[offset13] < c_b)
                                                                goto is_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            if(p[offset8] < c_b)
                                                if(p[offset9] < c_b)
                                                    if(p[offset10] < c_b)
                                                        if(p[offset11] < c_b)
                                                            if(p[offset12] < c_b)
                                                                if(p[offset13] < c_b)
                                                                    goto is_a_corner;
                                                                else
                                                                    goto is_not_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                            else if(p[offset7] < c_b)
                                if(p[offset3] < c_b)
                                    if(p[offset1] < c_b)
                                        if(p[offset6] < c_b)
                                            if(p[offset8] < c_b)
                                                goto is_a_corner;
                                            else
                                                if(p[offset15] < c_b)
                                                    goto is_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            if(p[offset13] < c_b)
                                                if(p[offset14] < c_b)
                                                    if(p[offset15] < c_b)
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                    else
                                        if(p[offset8] < c_b)
                                            if(p[offset9] < c_b)
                                                if(p[offset10] < c_b)
                                                    if(p[offset6] < c_b)
                                                        goto is_a_corner;
                                                    else
                                                        if(p[offset11] < c_b)
                                                            if(p[offset12] < c_b)
                                                                if(p[offset13] < c_b)
                                                                    if(p[offset14] < c_b)
                                                                        if(p[offset15] < c_b)
                                                                            goto is_a_corner;
                                                                        else
                                                                            goto is_not_a_corner;
                                                                    else
                                                                        goto is_not_a_corner;
                                                                else
                                                                    goto is_not_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                else
                                    if(p[offset10] < c_b)
                                        if(p[offset11] < c_b)
                                            if(p[offset12] < c_b)
                                                if(p[offset8] < c_b)
                                                    if(p[offset9] < c_b)
                                                        if(p[offset6] < c_b)
                                                            goto is_a_corner;
                                                        else
                                                            if(p[offset13] < c_b)
                                                                if(p[offset14] < c_b)
                                                                    if(p[offset15] < c_b)
                                                                        goto is_a_corner;
                                                                    else
                                                                        goto is_not_a_corner;
                                                                else
                                                                    goto is_not_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                    else
                                                        if(p[offset1] < c_b)
                                                            if(p[offset13] < c_b)
                                                                if(p[offset14] < c_b)
                                                                    if(p[offset15] < c_b)
                                                                        goto is_a_corner;
                                                                    else
                                                                        goto is_not_a_corner;
                                                                else
                                                                    goto is_not_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                else
                                                    if(p[offset1] < c_b)
                                                        if(p[offset13] < c_b)
                                                            if(p[offset14] < c_b)
                                                                if(p[offset15] < c_b)
                                                                    goto is_a_corner;
                                                                else
                                                                    goto is_not_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                            else
                                if(p[offset14] < c_b)
                                    if(p[offset15] < c_b)
                                        if(p[offset1] < c_b)
                                            if(p[offset3] < c_b)
                                                if(p[offset6] < c_b)
                                                    goto is_a_corner;
                                                else
                                                    if(p[offset13] < c_b)
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                            else
                                                if(p[offset10] < c_b)
                                                    if(p[offset11] < c_b)
                                                        if(p[offset12] < c_b)
                                                            if(p[offset13] < c_b)
                                                                goto is_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            if(p[offset8] < c_b)
                                                if(p[offset9] < c_b)
                                                    if(p[offset10] < c_b)
                                                        if(p[offset11] < c_b)
                                                            if(p[offset12] < c_b)
                                                                if(p[offset13] < c_b)
                                                                    goto is_a_corner;
                                                                else
                                                                    goto is_not_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                        else
                            if(p[offset12] > cb)
                                if(p[offset7] > cb)
                                    if(p[offset8] > cb)
                                        if(p[offset9] > cb)
                                            if(p[offset10] > cb)
                                                if(p[offset11] > cb)
                                                    if(p[offset13] > cb)
                                                        if(p[offset14] > cb)
                                                            if(p[offset6] > cb)
                                                                goto is_a_corner;
                                                            else
                                                                if(p[offset15] > cb)
                                                                    goto is_a_corner;
                                                                else
                                                                    goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                            else if(p[offset12] < c_b)
                                if(p[offset13] < c_b)
                                    if(p[offset14] < c_b)
                                        if(p[offset15] < c_b)
                                            if(p[offset1] < c_b)
                                                if(p[offset3] < c_b)
                                                    goto is_a_corner;
                                                else
                                                    if(p[offset10] < c_b)
                                                        if(p[offset11] < c_b)
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                            else
                                                if(p[offset8] < c_b)
                                                    if(p[offset9] < c_b)
                                                        if(p[offset10] < c_b)
                                                            if(p[offset11] < c_b)
                                                                goto is_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            if(p[offset6] < c_b)
                                                if(p[offset7] < c_b)
                                                    if(p[offset8] < c_b)
                                                        if(p[offset9] < c_b)
                                                            if(p[offset10] < c_b)
                                                                if(p[offset11] < c_b)
                                                                    goto is_a_corner;
                                                                else
                                                                    goto is_not_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                            else
                                goto is_not_a_corner;
                    else
                        if(p[offset11] > cb)
                            if(p[offset7] > cb)
                                if(p[offset8] > cb)
                                    if(p[offset9] > cb)
                                        if(p[offset10] > cb)
                                            if(p[offset12] > cb)
                                                if(p[offset13] > cb)
                                                    if(p[offset6] > cb)
                                                        if(p[offset5] > cb)
                                                            goto is_a_corner;
                                                        else
                                                            if(p[offset14] > cb)
                                                                goto is_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                    else
                                                        if(p[offset14] > cb)
                                                            if(p[offset15] > cb)
                                                                goto is_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                            else
                                goto is_not_a_corner;
                        else if(p[offset11] < c_b)
                            if(p[offset12] < c_b)
                                if(p[offset13] < c_b)
                                    if(p[offset10] < c_b)
                                        if(p[offset14] < c_b)
                                            if(p[offset15] < c_b)
                                                if(p[offset1] < c_b)
                                                    goto is_a_corner;
                                                else
                                                    if(p[offset8] < c_b)
                                                        if(p[offset9] < c_b)
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                            else
                                                if(p[offset6] < c_b)
                                                    if(p[offset7] < c_b)
                                                        if(p[offset8] < c_b)
                                                            if(p[offset9] < c_b)
                                                                goto is_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            if(p[offset5] < c_b)
                                                if(p[offset6] < c_b)
                                                    if(p[offset7] < c_b)
                                                        if(p[offset8] < c_b)
                                                            if(p[offset9] < c_b)
                                                                goto is_a_corner;
                                                            else
                                                                goto is_not_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                    else
                                        if(p[offset1] < c_b)
                                            if(p[offset3] < c_b)
                                                if(p[offset14] < c_b)
                                                    if(p[offset15] < c_b)
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                            else
                                goto is_not_a_corner;
                        else
                            goto is_not_a_corner;
                else
                    if(p[offset9] > cb)
                        if(p[offset7] > cb)
                            if(p[offset8] > cb)
                                if(p[offset10] > cb)
                                    if(p[offset11] > cb)
                                        if(p[offset6] > cb)
                                            if(p[offset5] > cb)
                                                if(p[offset4] > cb)
                                                    if(p[offset3] > cb)
                                                        goto is_a_corner;
                                                    else
                                                        if(p[offset12] > cb)
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                else
                                                    if(p[offset12] > cb)
                                                        if(p[offset13] > cb)
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                            else
                                                if(p[offset12] > cb)
                                                    if(p[offset13] > cb)
                                                        if(p[offset14] > cb)
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            if(p[offset12] > cb)
                                                if(p[offset13] > cb)
                                                    if(p[offset14] > cb)
                                                        if(p[offset15] > cb)
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                            else
                                goto is_not_a_corner;
                        else
                            goto is_not_a_corner;
                    else if(p[offset9] < c_b)
                        if(p[offset10] < c_b)
                            if(p[offset11] < c_b)
                                if(p[offset8] < c_b)
                                    if(p[offset12] < c_b)
                                        if(p[offset13] < c_b)
                                            if(p[offset14] < c_b)
                                                if(p[offset15] < c_b)
                                                    goto is_a_corner;
                                                else
                                                    if(p[offset6] < c_b)
                                                        if(p[offset7] < c_b)
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                            else
                                                if(p[offset5] < c_b)
                                                    if(p[offset6] < c_b)
                                                        if(p[offset7] < c_b)
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            if(p[offset4] < c_b)
                                                if(p[offset5] < c_b)
                                                    if(p[offset6] < c_b)
                                                        if(p[offset7] < c_b)
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                    else
                                        if(p[offset3] < c_b)
                                            if(p[offset4] < c_b)
                                                if(p[offset5] < c_b)
                                                    if(p[offset6] < c_b)
                                                        if(p[offset7] < c_b)
                                                            goto is_a_corner;
                                                        else
                                                            goto is_not_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                else
                                    if(p[offset1] < c_b)
                                        if(p[offset12] < c_b)
                                            if(p[offset13] < c_b)
                                                if(p[offset14] < c_b)
                                                    if(p[offset15] < c_b)
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                            else
                                goto is_not_a_corner;
                        else
                            goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
            else
                if(p[offset7] > cb)
                    if(p[offset8] > cb)
                        if(p[offset9] > cb)
                            if(p[offset6] > cb)
                                if(p[offset5] > cb)
                                    if(p[offset4] > cb)
                                        if(p[offset3] > cb)
                                            if(p[offset2] > cb)
                                                if(p[offset1] > cb)
                                                    goto is_a_corner;
                                                else
                                                    if(p[offset10] > cb)
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                            else
                                                if(p[offset10] > cb)
                                                    if(p[offset11] > cb)
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            if(p[offset10] > cb)
                                                if(p[offset11] > cb)
                                                    if(p[offset12] > cb)
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                    else
                                        if(p[offset10] > cb)
                                            if(p[offset11] > cb)
                                                if(p[offset12] > cb)
                                                    if(p[offset13] > cb)
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                else
                                    if(p[offset10] > cb)
                                        if(p[offset11] > cb)
                                            if(p[offset12] > cb)
                                                if(p[offset13] > cb)
                                                    if(p[offset14] > cb)
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                            else
                                if(p[offset10] > cb)
                                    if(p[offset11] > cb)
                                        if(p[offset12] > cb)
                                            if(p[offset13] > cb)
                                                if(p[offset14] > cb)
                                                    if(p[offset15] > cb)
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                        else
                            goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                else if(p[offset7] < c_b)
                    if(p[offset8] < c_b)
                        if(p[offset9] < c_b)
                            if(p[offset6] < c_b)
                                if(p[offset5] < c_b)
                                    if(p[offset4] < c_b)
                                        if(p[offset3] < c_b)
                                            if(p[offset2] < c_b)
                                                if(p[offset1] < c_b)
                                                    goto is_a_corner;
                                                else
                                                    if(p[offset10] < c_b)
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                            else
                                                if(p[offset10] < c_b)
                                                    if(p[offset11] < c_b)
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                        else
                                            if(p[offset10] < c_b)
                                                if(p[offset11] < c_b)
                                                    if(p[offset12] < c_b)
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                    else
                                        if(p[offset10] < c_b)
                                            if(p[offset11] < c_b)
                                                if(p[offset12] < c_b)
                                                    if(p[offset13] < c_b)
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                else
                                    if(p[offset10] < c_b)
                                        if(p[offset11] < c_b)
                                            if(p[offset12] < c_b)
                                                if(p[offset13] < c_b)
                                                    if(p[offset14] < c_b)
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                            else
                                if(p[offset10] < c_b)
                                    if(p[offset11] < c_b)
                                        if(p[offset12] < c_b)
                                            if(p[offset13] < c_b)
                                                if(p[offset14] < c_b)
                                                    if(p[offset15] < c_b)
                                                        goto is_a_corner;
                                                    else
                                                        goto is_not_a_corner;
                                                else
                                                    goto is_not_a_corner;
                                            else
                                                goto is_not_a_corner;
                                        else
                                            goto is_not_a_corner;
                                    else
                                        goto is_not_a_corner;
                                else
                                    goto is_not_a_corner;
                        else
                            goto is_not_a_corner;
                    else
                        goto is_not_a_corner;
                else
                    goto is_not_a_corner;

is_a_corner:
            bmin=b_test;
            goto end;

is_not_a_corner:
            bmax=b_test;
            goto end;

end:

            if(bmin == bmax - 1 || bmin == bmax)
                return bmin;
            b_test = (bmin + bmax) / 2;
        }
    }

    void OAST9_16::updateOffsets()
    {
        offset0=(-3)+(0)*_lastStride;
        offset1=(-3)+(-1)*_lastStride;
        offset2=(-2)+(-2)*_lastStride;
        offset3=(-1)+(-3)*_lastStride;
        offset4=(0)+(-3)*_lastStride;
        offset5=(1)+(-3)*_lastStride;
        offset6=(2)+(-2)*_lastStride;
        offset7=(3)+(-1)*_lastStride;
        offset8=(3)+(0)*_lastStride;
        offset9=(3)+(1)*_lastStride;
        offset10=(2)+(2)*_lastStride;
        offset11=(1)+(3)*_lastStride;
        offset12=(0)+(3)*_lastStride;
        offset13=(-1)+(3)*_lastStride;
        offset14=(-2)+(2)*_lastStride;
        offset15=(-3)+(1)*_lastStride;
    }
}
