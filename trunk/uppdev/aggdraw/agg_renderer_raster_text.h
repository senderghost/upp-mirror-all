//----------------------------------------------------------------------------
// Anti-Grain Geometry (AGG) - Version 2.5
// A high quality rendering engine for C++
// Copyright (C) 2002-2006 Maxim Shemanarev
// Contact: mcseem@antigrain.com
//          mcseemagg@yahoo.com
//          http://antigrain.com
// 
// AGG is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// AGG is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with AGG; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, 
// MA 02110-1301, USA.
//----------------------------------------------------------------------------

#ifndef AGG_RENDERER_RASTER_TEXT_INCLUDED
#define AGG_RENDERER_RASTER_TEXT_INCLUDED

#include "agg_basics.h"

namespace agg
{

    //==============================================renderer_raster_htext_solid
    template<class BaseRenderer, class GlyphGenerator> 
    class renderer_raster_htext_solid
    {
    public:
        typedef BaseRenderer ren_type;
        typedef GlyphGenerator glyph_gen_type;
        typedef typename glyph_gen_type::glyph_rect glyph_rect;
        typedef typename ren_type::color_type color_type;

        renderer_raster_htext_solid(ren_type& ren, glyph_gen_type& glyph) :
            m_ren(&ren),
            m_glyph(&glyph)
        {}
        void attach(ren_type& ren) { m_ren = &ren; }

        //--------------------------------------------------------------------
        void color(const color_type& c) { m_color = c; }
        const color_type& color() const { return m_color; }

        //--------------------------------------------------------------------
        template<class CharT>
        void render_text(double x, double y, const CharT* str, bool flip=false)
        {
            glyph_rect r;
            while(*str)
            {
                m_glyph->prepare(&r, x, y, *str, flip);
                if(r.x2 >= r.x1)
                {
                    int i;
                    if(flip)
                    {
                        for(i = r.y1; i <= r.y2; i++)
                        {
                            m_ren->blend_solid_hspan(r.x1, i, (r.x2 - r.x1 + 1),
                                                     m_color,
                                                     m_glyph->span(r.y2 - i));
                        }
                    }
                    else
                    {
                        for(i = r.y1; i <= r.y2; i++)
                        {
                            m_ren->blend_solid_hspan(r.x1, i, (r.x2 - r.x1 + 1),
                                                     m_color,
                                                     m_glyph->span(i - r.y1));
                        }
                    }
                }
                x += r.dx;
                y += r.dy;
                ++str;
            }
        }

    private:
        ren_type* m_ren;
        glyph_gen_type* m_glyph;
        color_type m_color;
    };



    //=============================================renderer_raster_vtext_solid
    template<class BaseRenderer, class GlyphGenerator> 
    class renderer_raster_vtext_solid
    {
    public:
        typedef BaseRenderer ren_type;
        typedef GlyphGenerator glyph_gen_type;
        typedef typename glyph_gen_type::glyph_rect glyph_rect;
        typedef typename ren_type::color_type color_type;

        renderer_raster_vtext_solid(ren_type& ren, glyph_gen_type& glyph) :
            m_ren(&ren),
            m_glyph(&glyph)
        {
        }

        //--------------------------------------------------------------------
        void color(const color_type& c) { m_color = c; }
        const color_type& color() const { return m_color; }

        //--------------------------------------------------------------------
        template<class CharT>
        void render_text(double x, double y, const CharT* str, bool flip=false)
        {
            glyph_rect r;
            while(*str)
            {
                m_glyph->prepare(&r, x, y, *str, !flip);
                if(r.x2 >= r.x1)
                {
                    int i;
                    if(flip)
                    {
                        for(i = r.y1; i <= r.y2; i++)
                        {
                            m_ren->blend_solid_vspan(i, r.x1, (r.x2 - r.x1 + 1),
                                                     m_color,
                                                     m_glyph->span(i - r.y1));
                        }
                    }
                    else
                    {
                        for(i = r.y1; i <= r.y2; i++)
                        {
                            m_ren->blend_solid_vspan(i, r.x1, (r.x2 - r.x1 + 1),
                                                     m_color,
                                                     m_glyph->span(r.y2 - i));
                        }
                    }
                }
                x += r.dx;
                y += r.dy;
                ++str;
            }
        }

    private:
        ren_type* m_ren;
        glyph_gen_type* m_glyph;
        color_type m_color;
    };






    //===================================================renderer_raster_htext
    template<class ScanlineRenderer, class GlyphGenerator> 
    class renderer_raster_htext
    {
    public:
        typedef ScanlineRenderer ren_type;
        typedef GlyphGenerator glyph_gen_type;
        typedef typename glyph_gen_type::glyph_rect glyph_rect;

        class scanline_single_span
        {
        public:
            typedef agg::cover_type cover_type;

            //----------------------------------------------------------------
            struct const_span
            {
                int x;
                unsigned len;
                const cover_type* covers;

                const_span() {}
                const_span(int x_, unsigned len_, const cover_type* covers_) :
                    x(x_), len(len_), covers(covers_) 
                {}
            };

            typedef const const_span* const_iterator;

            //----------------------------------------------------------------
            scanline_single_span(int x, int y, unsigned len, 
                                 const cover_type* covers) :
                m_y(y),
                m_span(x, len, covers)
            {}

            //----------------------------------------------------------------
            int      y()           const { return m_y; }
            unsigned num_spans()   const { return 1;   }
            const_iterator begin() const { return &m_span; }

        private:
            //----------------------------------------------------------------
            int m_y;
            const_span m_span;
        };



        //--------------------------------------------------------------------
        renderer_raster_htext(ren_type& ren, glyph_gen_type& glyph) :
            m_ren(&ren),
            m_glyph(&glyph)
        {
        }


        //--------------------------------------------------------------------
        template<class CharT>
        void render_text(double x, double y, const CharT* str, bool flip=false)
        {
            glyph_rect r;
            while(*str)
            {
                m_glyph->prepare(&r, x, y, *str, flip);
                if(r.x2 >= r.x1)
                {
                    m_ren->prepare();
                    int i;
                    if(flip)
                    {
                        for(i = r.y1; i <= r.y2; i++)
                        {
                            m_ren->render(
                                scanline_single_span(r.x1, 
                                                     i, 
                                                     (r.x2 - r.x1 + 1),
                                                     m_glyph->span(r.y2 - i)));
                        }
                    }
                    else
                    {
                        for(i = r.y1; i <= r.y2; i++)
                        {
                            m_ren->render(
                                scanline_single_span(r.x1, 
                                                     i, 
                                                     (r.x2 - r.x1 + 1),
                                                     m_glyph->span(i - r.y1)));
                        }
                    }
                }
                x += r.dx;
                y += r.dy;
                ++str;
            }
        }

    private:
        ren_type* m_ren;
        glyph_gen_type* m_glyph;
    };




}

#endif

