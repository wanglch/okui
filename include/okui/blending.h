/**
* Copyright 2017 BitTorrent Inc.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*    http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/
#pragma once

#include <okui/config.h>

#include <okui/opengl/blending.h>

namespace okui {

using opengl::BlendFactor;

struct BlendFunction {
    BlendFactor sourceRGB = BlendFactor::kOne;
    BlendFactor destinationRGB = BlendFactor::kZero;
    BlendFactor sourceAlpha = BlendFactor::kOne;
    BlendFactor destinationAlpha = BlendFactor::kZero;

    /**
    * okui shaders will do the appropriate conversions to make sure the source alpha is premultiplied when it should be.
    */
    bool premultipliedSourceAlpha = false;

    constexpr bool operator==(const BlendFunction& f) const {
        return sourceRGB == f.sourceRGB && destinationRGB == f.destinationRGB && sourceAlpha == f.sourceAlpha
            && destinationAlpha == f.destinationAlpha && premultipliedSourceAlpha == f.premultipliedSourceAlpha;
    }

    /**
    * The default blend function simply draws to the destination.
    */
    static BlendFunction kDefault;

    /**
    * Alpha lock prevents the destination color from becoming more or less opaque. It's useful for recoloring
    * sections of previously drawn shapes.
    */
    static BlendFunction kAlphaLock;

    /**
    * Erasure removes color components or opacity from the destination.
    *
    * Each channel is erased independently of any others, including the alpha channel. For example, to erase
    * all red from the destination, the (1.0, 0.0, 0.0, 0.0) color should be used.
    */
    static BlendFunction kErasure;
};

class Blending {
public:
    Blending(const BlendFunction& function);
    Blending(BlendFactor sourceRGB, BlendFactor destinationRGB, BlendFactor sourceAlpha, BlendFactor destinationAlpha, bool premultipliedSourceAlpha);
    ~Blending();

    static const BlendFunction& Current() {
        return _sBlendFunction;
    }

private:
    BlendFunction _previous;

    static BlendFunction _sBlendFunction;
    static int _sBlendingDepth;

    static void SetBlendFunction(const BlendFunction& function, BlendFunction* previous = nullptr);
};

} // namespace okui
