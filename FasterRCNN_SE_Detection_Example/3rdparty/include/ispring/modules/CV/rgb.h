﻿/**
* @file		rgb.h
* @author		kimbomm (springnode@gmail.com)
* @date		2017. 10. 04...
* @version	1.0.0
*
*  @brief
*			RGB 색상표 파일
*			https://xkcd.com/color/rgb/
*	@remark
*			Created by kimbom on 2017. 10. 04...
*			Copyright 2017 kimbom.All rights reserved.
*/

#if !defined(ISPRING_7E1_A_4_RGB_HPP_INCLUDED)
#define ISPRING_7E1_A_4_RGB_HPP_INCLUDED

#include<vector>
#include<opencv2/opencv.hpp>
#include"../defines.h"
#ifndef DOXYGEN
namespace ispring_3rdparty {
	SELECT_ANY std::vector<cv::Scalar> color_map = {
		{ 126,30,156 },		//purple
		{ 21,176,26 },		//green
		{ 3,67,223 },		//blue
		{ 255,129,192 },		//pink
		{ 101,55,0 },		//brown
		{ 229,0,0 },		//red
		{ 149,208,252 },		//light blue
		{ 2,147,134 },		//teal
		{ 249,115,6 },		//orange
		{ 150,249,123 },		//light green
		{ 194,0,120 },		//magenta
		{ 255,255,20 },		//yellow
		{ 117,187,253 },		//sky blue
		{ 146,149,145 },		//grey
		{ 137,254,5 },		//lime green
		{ 191,119,246 },		//light purple
		{ 154,14,234 },		//violet
		{ 6,194,172 },		//turquoise
		{ 199,159,239 },		//lavender
		{ 209,178,111 },		//tan
		{ 0,255,255 },		//cyan
		{ 19,234,201 },		//aqua
		{ 174,113,129 },		//mauve
		{ 1,255,7 },		//bright green
		{ 101,0,33 },		//maroon
		{ 110,117,14 },		//olive
		{ 255,121,108 },		//salmon
		{ 230,218,166 },		//beige
		{ 5,4,170 },		//royal blue
		{ 206,162,253 },		//lilac
		{ 255,2,141 },		//hot pink
		{ 173,129,80 },		//light brown
		{ 199,253,181 },		//pale green
		{ 255,176,124 },		//peach
		{ 103,122,4 },		//olive green
		{ 203,65,107 },		//dark pink
		{ 142,130,254 },		//periwinkle
		{ 83,252,161 },		//sea green
		{ 170,255,50 },		//lime
		{ 56,2,130 },		//indigo
		{ 206,179,1 },		//mustard
		{ 255,209,223 },		//light pink
		{ 207,98,117 },		//rose
		{ 1,101,252 },		//bright blue
		{ 12,255,12 },		//neon green
		{ 192,78,1 },		//burnt orange
		{ 4,216,178 },		//aquamarine
		{ 63,155,11 },		//grass green
		{ 208,254,254 },		//pale blue
		{ 132,0,0 },		//dark red
		{ 190,3,253 },		//bright purple
		{ 192,251,45 },		//yellow green
		{ 162,207,254 },		//baby blue
		{ 219,180,12 },		//gold
		{ 143,255,159 },		//mint green
		{ 88,15,65 },		//plum
		{ 75,0,110 },		//royal purple
		{ 143,20,2 },		//brick red
		{ 1,77,78 },		//dark teal
		{ 97,0,35 },		//burgundy
		{ 170,166,98 },		//khaki
		{ 19,126,109 },		//blue green
		{ 122,249,171 },		//seafoam green
		{ 2,171,46 },		//kelly green
		{ 154,174,7 },		//puke green
		{ 142,171,18 },		//pea green
		{ 185,162,129 },		//taupe
		{ 193,248,10 },		//chartreuse
		{ 254,1,177 },		//bright pink
		{ 253,170,72 },		//light orange
		{ 159,254,176 },		//mint
		{ 176,255,157 },		//pastel green
		{ 226,202,118 },		//sand
		{ 198,81,2 },		//dark orange
		{ 169,249,113 },		//spring green
		{ 165,126,82 },		//puce
		{ 128,249,173 },		//seafoam
		{ 107,139,164 },		//grey blue
		{ 75,93,22 },		//army green
		{ 54,55,55 },		//dark grey
		{ 213,182,10 },		//dark yellow
		{ 250,194,5 },		//goldenrod
		{ 81,101,114 },		//slate
		{ 144,228,193 },		//light teal
		{ 168,60,9 },		//rust
		{ 255,207,220 },		//pale pink
		{ 4,133,209 },		//cerulean
		{ 255,71,76 },		//light red
		{ 210,189,10 },		//mustard yellow
		{ 191,144,5 },		//ochre
		{ 255,255,132 },		//pale yellow
		{ 140,0,15 },		//crimson
		{ 237,13,217 },		//fuchsia
		{ 96,124,142 },		//blue grey
		{ 91,124,153 },		//slate blue
		{ 183,144,212 },		//pale purple
		{ 4,116,149 },		//sea blue
		{ 214,72,215 },		//pinkish purple
		{ 165,165,2 },		//puke
		{ 216,220,214 },		//light grey
		{ 92,169,4 },		//leaf green
		{ 255,254,122 },		//light yellow
		{ 90,125,154 },		//steel blue
		{ 101,139,56 },		//moss green
		{ 152,239,249 },		//robin's egg blue
		{ 255,255,255 },		//white
		{ 120,155,115 },		//grey green
		{ 135,174,115 },		//sage
		{ 160,54,35 },		//brick
		{ 176,78,15 },		//burnt sienna
		{ 127,43,10 },		//reddish brown
		{ 255,255,194 },		//cream
		{ 252,90,80 },		//coral
		{ 3,113,156 },		//ocean blue
		{ 64,163,104 },		//greenish
		{ 150,0,86 },		//dark magenta
		{ 253,60,6 },		//red orange
		{ 112,59,231 },		//bluish purple
		{ 214,180,252 },		//light violet
		{ 192,115,122 },		//dusty rose
		{ 44,111,187 },		//medium blue
		{ 205,253,2 },		//greenish yellow
		{ 176,221,22 },		//yellowish green
		{ 96,30,249 },		//purplish blue
		{ 94,129,157 },		//greyish blue
		{ 108,52,97 },		//grape
		{ 172,191,105 },		//light olive
		{ 81,112,215 },		//cornflower blue
		{ 241,12,69 },		//pinkish red
		{ 255,0,13 },		//bright red
		{ 6,154,243 },		//azure
		{ 87,41,206 },		//blue purple
		{ 4,92,90 },		//dark turquoise
		{ 6,82,255 },		//electric blue
		{ 255,255,228 },		//off white
		{ 177,209,252 },		//powder blue
		{ 128,1,63 },		//wine
		{ 116,166,98 },		//dull green
		{ 118,205,38 },		//apple green
		{ 126,244,204 },		//light turquoise
		{ 188,19,254 },		//neon purple
		{ 30,72,143 },		//cobalt
		{ 212,106,126 },		//pinkish
		{ 111,118,50 },		//olive drab
		{ 10,136,138 },		//dark cyan
		{ 99,45,233 },		//purple blue
		{ 133,103,152 },		//dark lavender
		{ 162,164,21 },		//vomit
		{ 255,167,86 },		//pale orange
		{ 11,139,135 },		//greenish blue
		{ 175,136,74 },		//dark tan
		{ 6,180,139 },		//green blue
		{ 16,166,116 },		//bluish green
		{ 162,191,254 },		//pastel blue
		{ 118,153,88 },		//moss
		{ 92,172,45 },		//grass
		{ 203,1,98 },		//deep pink
		{ 152,0,2 },		//blood red
		{ 136,179,120 },		//sage green
		{ 2,216,233 },		//aqua blue
		{ 202,102,65 },		//terracotta
		{ 202,160,255 },		//pastel purple
		{ 169,86,30 },		//sienna
		{ 201,255,39 },		//green yellow
		{ 190,1,25 },		//scarlet
		{ 130,166,125 },		//greyish green
		{ 93,6,233 },		//blue violet
		{ 106,121,247 },		//cornflower
		{ 255,183,206 },		//baby pink
		{ 52,56,55 },		//charcoal
		{ 225,119,1 },		//pumpkin
		{ 105,97,18 },		//greenish brown
		{ 139,46,22 },		//red brown
		{ 106,110,9 },		//brownish green
		{ 255,148,8 },		//tangerine
		{ 254,123,124 },		//salmon pink
		{ 18,225,147 },		//aqua green
		{ 176,1,73 },		//raspberry
		{ 136,113,145 },		//greyish purple
		{ 247,135,154 },		//rose pink
		{ 254,1,154 },		//neon pink
		{ 3,10,167 },		//cobalt blue
		{ 190,100,0 },		//orange brown
		{ 154,2,0 },		//deep red
		{ 253,65,30 },		//orange red
		{ 205,197,10 },		//dirty yellow
		{ 200,117,196 },		//orchid
		{ 254,44,84 },		//reddish pink
		{ 145,9,81 },		//reddish purple
		{ 252,176,1 },		//yellow orange
		{ 172,255,252 },		//light cyan
		{ 130,202,252 },		//sky
		{ 250,95,247 },		//light magenta
		{ 217,84,77 },		//pale red
		{ 1,160,73 },		//emerald
		{ 172,147,98 },		//dark beige
		{ 122,151,3 },		//ugly green
		{ 31,167,116 },		//jade
		{ 150,174,141 },		//greenish grey
		{ 200,90,83 },		//dark salmon
		{ 206,93,174 },		//purplish pink
		{ 5,105,107 },		//dark aqua
		{ 203,119,35 },		//brownish orange
		{ 164,190,92 },		//light olive green
		{ 140,255,219 },		//light aqua
		{ 182,106,80 },		//clay
		{ 57,173,72 },		//medium green
		{ 160,69,14 },		//burnt umber
		{ 73,117,156 },		//dull blue
		{ 177,145,110 },		//pale brown
		{ 2,143,30 },		//emerald green
		{ 156,109,87 },		//brownish
		{ 115,92,18 },		//mud
		{ 181,72,93 },		//dark rose
		{ 158,54,35 },		//brownish red
		{ 219,75,218 },		//pink purple
		{ 201,76,190 },		//pinky purple
		{ 82,101,37 },		//camo green
		{ 123,178,116 },		//faded green
		{ 213,138,148 },		//dusty pink
		{ 224,63,216 },		//purple pink
		{ 137,162,3 },		//vomit green
		{ 248,72,28 },		//reddish orange
		{ 213,134,157 },		//dull pink
		{ 68,142,228 },		//dark sky blue
		{ 209,255,189 },		//very light green
		{ 255,186,205 },		//pastel pink
		{ 130,109,140 },		//grey purple
		{ 213,255,255 },		//very light blue
		{ 135,76,98 },		//dark mauve
		{ 78,116,150 },		//cadet blue
		{ 215,255,254 },		//ice blue
		{ 251,238,172 },		//light tan
		{ 102,126,44 },		//dirty green
		{ 4,217,255 },		//neon blue
		{ 123,3,35 },		//wine red
		{ 132,89,126 },		//dull purple
		{ 183,148,0 },		//yellow brown
		{ 59,99,140 },		//denim
		{ 255,255,212 },		//eggshell
		{ 4,130,67 },		//jungle green
		{ 222,126,93 },		//dark peach
		{ 127,94,0 },		//poop
		{ 178,100,0 },		//umber
		{ 223,197,254 },		//light lavender
		{ 255,253,1 },		//bright yellow
		{ 254,198,21 },		//golden yellow
		{ 90,134,173 },		//dusty blue
		{ 33,252,13 },		//electric green
		{ 117,253,99 },		//lighter green
		{ 89,101,109 },		//slate grey
		{ 37,163,111 },		//teal green
		{ 1,56,106 },		//marine blue
		{ 144,177,52 },		//avocado
		{ 201,100,59 },		//terra cotta
		{ 130,95,135 },		//dusty purple
		{ 162,72,87 },		//light maroon
		{ 196,66,64 },		//reddish
		{ 156,109,165 },		//dark lilac
		{ 102,95,209 },		//dark periwinkle
		{ 116,139,151 },		//bluish grey
		{ 194,190,14 },		//puke yellow
		{ 148,86,140 },		//purplish
		{ 32,0,177 },		//ultramarine
		{ 160,4,152 },		//barney purple
		{ 146,153,1 },		//pea soup
		{ 201,176,3 },		//brownish yellow
		{ 1,249,198 },		//bright teal
		{ 1,122,121 },		//bluegreen
		{ 84,78,3 },		//green brown
		{ 85,57,204 },		//blurple
		{ 198,252,255 },		//light sky blue
		{ 143,153,251 },		//periwinkle blue
		{ 206,174,250 },		//pale violet
		{ 8,120,4 },		//darker green
		{ 1,15,204 },		//true blue
		{ 119,146,111 },		//green grey
		{ 127,112,83 },		//grey brown
		{ 60,77,3 },		//dark olive green
		{ 255,177,109 },		//apricot
		{ 145,110,153 },		//faded purple
		{ 1,18,136 },		//darker blue
		{ 222,12,98 },		//cerise
		{ 114,134,57 },		//khaki green
		{ 159,35,5 },		//burnt red
		{ 79,145,83 },		//light forest green
		{ 81,10,201 },		//violet blue
		{ 238,207,254 },		//pale lavender
		{ 143,254,9 },		//acid green
		{ 134,111,133 },		//purple grey
		{ 253,255,82 },		//lemon
		{ 255,91,0 },		//bright orange
		{ 111,194,118 },		//soft green
		{ 242,158,142 },		//blush
		{ 155,122,1 },		//yellowish brown
		{ 8,255,8 },		//fluorescent green
		{ 170,35,255 },		//electric purple
		{ 115,133,149 },		//steel
		{ 216,134,59 },		//dull orange
		{ 101,116,50 },		//muddy green
		{ 252,192,6 },		//marigold
		{ 1,123,146 },		//ocean
		{ 194,146,161 },		//light mauve
		{ 123,0,44 },		//bordeaux
		{ 126,251,179 },		//light blue green
		{ 250,238,102 },		//yellowish
		{ 157,193,0 },		//snot green
		{ 185,255,102 },		//light lime green
		{ 116,149,81 },		//drab green
		{ 101,140,187 },		//faded blue
		{ 203,0,245 },		//hot purple
		{ 112,108,17 },		//brown green
		{ 116,133,0 },		//swamp green
		{ 109,90,207 },		//light indigo
		{ 95,52,231 },		//purpley blue
		{ 61,122,253 },		//lightish blue
		{ 1,136,159 },		//teal blue
		{ 59,91,146 },		//denim blue
		{ 126,189,1 },		//dark lime green
		{ 238,220,91 },		//dull yellow
		{ 192,250,139 },		//pistachio
		{ 253,255,56 },		//lemon yellow
		{ 158,1,104 },		//red violet
		{ 204,122,139 },		//dusky pink
		{ 138,110,69 },		//dirt
		{ 158,67,162 },		//medium purple
		{ 127,95,0 },		//shit
		{ 168,137,5 },		//dark mustard
		{ 148,166,23 },		//pea soup green
		{ 254,131,204 },		//bubblegum pink
		{ 254,70,165 },		//barbie pink
		{ 102,124,62 },		//military green
		{ 130,203,178 },		//pale teal
		{ 168,121,0 },		//bronze
		{ 252,38,71 },		//pinky red
		{ 187,63,63 },		//dull red
		{ 1,65,130 },		//darkish blue
		{ 41,118,187 },		//bluish
		{ 181,148,16 },		//dark gold
		{ 191,241,40 },		//yellowy green
		{ 43,93,52 },		//pine
		{ 0,82,73 },		//dark blue green
		{ 202,123,128 },		//dirty pink
		{ 101,141,109 },		//slate green
		{ 0,69,119 },		//prussian blue
		{ 173,10,253 },		//bright violet
		{ 165,90,244 },		//lighter purple
		{ 111,130,138 },		//steel grey
		{ 161,57,5 },		//russet
		{ 244,50,12 },		//vermillion
		{ 122,106,79 },		//greyish brown
		{ 130,7,71 },		//red purple
		{ 250,42,85 },		//red pink
		{ 15,254,249 },		//bright turquoise
		{ 178,122,1 },		//golden brown
		{ 5,110,238 },		//cerulean blue
		{ 100,136,234 },		//soft blue
		{ 140,253,126 },		//easter green
		{ 254,179,8 },		//amber
		{ 39,106,179 },		//mid blue
		{ 123,88,4 },		//shit brown
		{ 155,229,170 },		//hospital green
		{ 97,64,239 },		//purpleish blue
		{ 102,26,238 },		//purply blue
		{ 197,201,199 },		//silver
		{ 148,178,28 },		//sickly green
		{ 255,120,85 },		//melon
		{ 186,104,115 },		//dusky rose
		{ 185,105,2 },		//brown orange
		{ 40,124,55 },		//darkish green
		{ 158,0,58 },		//cranberry
		{ 152,86,141 },		//purpleish
		{ 254,255,202 },		//ecru
		{ 95,27,107 },		//darker purple
		{ 157,118,81 },		//mocha
		{ 255,8,232 },		//bright magenta
		{ 166,129,76 },		//coffee
		{ 152,94,43 },		//sepia
		{ 211,73,78 },		//faded red
		{ 255,254,64 },		//canary yellow
		{ 98,65,199 },		//bluey purple
		{ 255,254,113 },		//pastel yellow
		{ 165,251,213 },		//pale turquoise
		{ 200,141,148 },		//greyish pink
		{ 4,46,96 },		//marine
		{ 122,104,127 },		//purplish grey
		{ 198,159,89 },		//camel
		{ 134,119,95 },		//brownish grey
		{ 213,171,9 },		//burnt yellow
		{ 247,2,42 },		//cherry red
		{ 177,96,2 },		//orangey brown
		{ 253,176,192 },		//soft pink
		{ 17,135,93 },		//dark sea green
		{ 46,232,187 },		//aqua marine
		{ 138,241,254 },		//robin egg blue
		{ 152,246,176 },		//light sea green
		{ 96,70,15 },		//mud brown
		{ 201,174,116 },		//sandstone
		{ 222,157,172 },		//faded pink
		{ 244,208,84 },		//maize
		{ 198,156,4 },		//ocre
		{ 255,173,1 },		//orange yellow
		{ 155,143,85 },		//dark khaki
		{ 174,253,108 },		//light lime
		{ 38,247,253 },		//bright light blue
		{ 43,175,106 },		//jade green
		{ 172,29,184 },		//barney
		{ 189,108,72 },		//adobe
		{ 11,247,125 },		//minty green
		{ 46,90,136 },		//light navy blue
		{ 118,169,115 },		//dusty green
		{ 61,153,115 },		//ocean green
		{ 168,181,4 },		//mustard green
		{ 122,89,1 },		//poop brown
		{ 100,84,3 },		//olive brown
		{ 245,5,79 },		//pink red
		{ 21,80,132 },		//light navy
		{ 246,206,252 },		//very light purple
		{ 255,255,203 },		//ivory
		{ 199,96,255 },		//bright lavender
		{ 11,249,234 },		//bright aqua
		{ 109,237,253 },		//robin's egg
		{ 95,160,82 },		//muted green
		{ 127,81,18 },		//medium brown
		{ 182,99,37 },		//copper
		{ 132,183,1 },		//dark lime
		{ 251,41,67 },		//strawberry
		{ 131,101,57 },		//dirt brown
		{ 193,253,149 },		//celery
		{ 2,204,254 },		//bright sky blue
		{ 136,95,1 },		//poo brown
		{ 177,114,97 },		//pinkish brown
		{ 190,253,183 },		//celadon
		{ 101,254,8 },		//bright lime green
		{ 154,48,1 },		//auburn
		{ 254,2,162 },		//shocking pink
		{ 146,10,78 },		//mulberry
		{ 138,184,254 },		//carolina blue
		{ 97,225,96 },		//lightish green
		{ 237,200,255 },		//light lilac
		{ 185,204,129 },		//pale olive
		{ 251,125,7 },		//pumpkin orange
		{ 203,157,6 },		//yellow ochre
		{ 254,0,2 },		//fire engine red
		{ 13,117,248 },		//deep sky blue
		{ 253,70,89 },		//watermelon
		{ 251,221,126 },		//wheat
		{ 108,122,14 },		//murky green
		{ 118,66,78 },		//brownish purple
		{ 92,178,0 },		//kermit green
		{ 8,4,249 },		//primary blue
		{ 250,66,36 },		//orangey red
		{ 228,203,255 },		//pale lilac
		{ 170,39,4 },		//rust red
		{ 200,118,6 },		//dirty orange
		{ 200,172,169 },		//pinkish grey
		{ 157,87,131 },		//light plum
		{ 66,179,149 },		//greeny blue
		{ 239,29,231 },		//pink/purple
		{ 1,149,41 },		//irish green
		{ 147,124,0 },		//baby poop
		{ 153,204,4 },		//slime green
		{ 176,5,75 },		//purplish red
		{ 171,18,57 },		//rouge
		{ 255,197,203 },		//light rose
		{ 130,131,68 },		//drab
		{ 204,253,127 },		//light yellow green
		{ 192,113,254 },		//easter purple
		{ 172,187,13 },		//snot
		{ 254,169,147 },		//light salmon
		{ 200,60,185 },		//purpley pink
		{ 143,115,3 },		//poo
		{ 153,15,75 },		//berry
		{ 125,127,124 },		//medium grey
		{ 146,43,5 },		//brown red
		{ 166,111,181 },		//soft purple
		{ 195,144,155 },		//grey pink
		{ 43,177,121 },		//bluey green
		{ 31,9,84 },		//dark indigo
		{ 151,138,132 },		//warm grey
		{ 196,166,97 },		//sandy brown
		{ 207,2,52 },		//cherry
		{ 90,6,239 },		//blue/purple
		{ 83,98,103 },		//gunmetal
		{ 73,6,72 },		//deep violet
		{ 42,126,25 },		//tree green
		{ 178,95,3 },		//orangish brown
		{ 2,193,77 },		//shamrock green
		{ 244,54,5 },		//orangish red
		{ 198,248,8 },		//greeny yellow
		{ 208,193,1 },		//ugly yellow
		{ 67,107,173 },		//french blue
		{ 137,91,123 },		//dusky purple
		{ 255,253,116 },		//butter yellow
		{ 255,254,182 },		//light beige
		{ 245,191,3 },		//golden
		{ 71,95,148 },		//dusky blue
		{ 123,200,246 },		//lightblue
		{ 240,117,230 },		//purply pink
		{ 107,163,83 },		//off green
		{ 191,155,12 },		//ocher
		{ 127,78,30 },		//milk chocolate
		{ 255,216,177 },		//light peach
		{ 160,2,92 },		//deep magenta
		{ 175,111,9 },		//caramel
		{ 50,191,132 },		//greenish teal
		{ 190,253,115 },		//pale lime
		{ 153,1,71 },		//purple red
		{ 70,65,150 },		//blueberry
		{ 119,171,86 },		//asparagus
		{ 253,253,254 },		//pale grey
		{ 157,188,212 },		//light grey blue
		{ 177,255,101 },		//pale lime green
		{ 65,156,3 },		//grassy green
		{ 99,139,39 },		//mossy green
		{ 162,101,62 },		//earth
		{ 220,77,1 },		//deep orange
		{ 184,255,235 },		//pale aqua
		{ 190,1,60 },		//rose red
		{ 173,165,135 },		//stone
		{ 205,89,9 },		//rusty orange
		{ 164,191,32 },		//pea
		{ 157,185,44 },		//sick green
		{ 196,56,127 },		//darker pink
		{ 116,40,2 },		//chestnut
		{ 15,155,142 },		//blue/green
		{ 155,95,192 },		//amethyst
		{ 32,192,115 },		//dark mint green
		{ 253,193,197 },		//pale rose
		{ 59,113,159 },		//muted blue
		{ 207,175,123 },		//fawn
		{ 254,246,158 },		//buff
		{ 4,244,137 },		//turquoise green
		{ 136,104,6 },		//muddy brown
		{ 60,153,146 },		//sea
		{ 239,64,38 },		//tomato
		{ 255,127,167 },		//carnation pink
		{ 255,255,126 },		//banana
		{ 207,255,4 },		//neon yellow
		{ 168,164,149 },		//greyish
		{ 80,167,71 },		//mid green
		{ 128,91,135 },		//muted purple
		{ 255,4,144 },		//electric pink
		{ 241,218,122 },		//sandy
		{ 205,117,132 },		//ugly pink
		{ 6,177,196 },		//turquoise blue
		{ 168,65,91 },		//light burgundy
		{ 188,203,122 },		//greenish tan
		{ 72,192,114 },		//dark mint
		{ 179,111,246 },		//light urple
		{ 255,114,76 },		//pinkish orange
		{ 203,248,95 },		//pear
		{ 36,188,168 },		//tealish
		{ 143,140,231 },		//perrywinkle
		{ 255,171,15 },		//yellowish orange
		{ 255,150,79 },		//pastel orange
		{ 98,88,196 },		//iris
		{ 24,5,219 },		//ultramarine blue
		{ 53,83,10 },		//navy green
		{ 24,209,123 },		//seaweed
		{ 156,239,67 },		//kiwi
		{ 10,255,2 },		//fluro green
		{ 45,254,84 },		//bright light green
		{ 47,239,16 },		//vivid green
		{ 88,188,8 },		//frog green
		{ 135,110,75 },		//dull brown
		{ 78,84,129 },		//dusk
		{ 172,126,4 },		//mustard brown
		{ 81,183,59 },		//leafy green
		{ 73,132,184 },		//cool blue
		{ 200,253,61 },		//yellow/green
		{ 217,79,245 },		//heliotrope
		{ 94,220,31 },		//green apple
		{ 143,152,5 },		//baby poop green
		{ 110,203,60 },		//apple
		{ 223,78,200 },		//purpleish pink
		{ 115,0,57 },		//merlot
		{ 118,255,123 },		//lightgreen
		{ 236,45,1 },		//tomato red
		{ 174,255,110 },		//key lime
		{ 183,255,250 },		//pale cyan
		{ 199,193,12 },		//vomit yellow
		{ 107,66,71 },		//purplish brown
		{ 255,108,181 },		//bubblegum
		{ 1,180,76 },		//shamrock
		{ 255,166,43 },		//mango
		{ 208,254,29 },		//lime yellow
		{ 37,255,41 },		//hot green
		{ 93,20,81 },		//grape purple
		{ 240,148,77 },		//faded orange
		{ 135,169,34 },		//avocado green
		{ 1,103,149 },		//peacock blue
		{ 58,229,127 },		//weird green
		{ 201,94,251 },		//bright lilac
		{ 84,141,68 },		//fern green
		{ 63,130,157 },		//dirty blue
		{ 196,85,8 },		//rust orange
		{ 164,132,172 },		//heather
		{ 0,85,90 },		//deep teal
		{ 31,181,122 },		//dark seafoam
		{ 171,144,4 },		//baby poo
		{ 187,249,15 },		//yellowgreen
		{ 188,236,172 },		//light sage
		{ 123,253,199 },		//light aquamarine
		{ 30,248,118 },		//spearmint
		{ 135,253,5 },		//bright lime
		{ 10,221,8 },		//vibrant green
		{ 207,253,188 },		//very pale green
		{ 254,255,127 },		//faded yellow
		{ 181,195,6 },		//bile
		{ 30,145,103 },		//viridian
		{ 255,244,242 },		//very light pink
		{ 148,119,6 },		//puke brown
		{ 243,97,150 },		//medium pink
		{ 164,66,160 },		//ugly purple
		{ 255,253,55 },		//sunshine yellow
		{ 53,173,107 },		//seaweed green
		{ 193,198,252 },		//light periwinkle
		{ 173,248,2 },		//lemon green
		{ 105,96,6 },		//greeny brown
		{ 41,70,91 },		//dark grey blue
		{ 156,187,4 },		//bright olive
		{ 117,184,79 },		//turtle green
		{ 189,246,254 },		//pale sky blue
		{ 247,213,96 },		//light mustard
		{ 159,131,3 },		//diarrhea
		{ 1,115,113 },		//dark aquamarine
		{ 194,126,121 },		//brownish pink
		{ 136,151,23 },		//baby shit green
		{ 135,86,228 },		//purpley
		{ 119,161,181 },		//greyblue
		{ 245,4,201 },		//hot magenta
		{ 117,141,163 },		//blue/grey
		{ 255,249,208 },		//pale
		{ 51,184,100 },		//cool green
		{ 253,238,115 },		//sandy yellow
		{ 196,255,247 },		//eggshell blue
		{ 148,172,2 },		//barf green
		{ 140,255,158 },		//baby green
		{ 173,3,222 },		//vibrant purple
		{ 141,132,104 },		//brown grey
		{ 14,135,204 },		//water blue
		{ 192,2,47 },		//lipstick red
		{ 250,254,75 },		//banana yellow
		{ 168,125,194 },		//wisteria
		{ 103,58,63 },		//purple brown
		{ 178,151,5 },		//brown yellow
		{ 215,37,222 },		//purple/pink
		{ 191,254,40 },		//lemon lime
		{ 100,125,142 },		//grey/blue
		{ 185,72,78 },		//dusty red
		{ 199,71,103 },		//deep rose
		{ 62,175,118 },		//dark seafoam green
		{ 191,172,5 },		//muddy yellow
		{ 253,121,143 },		//carnation
		{ 174,139,12 },		//yellowy brown
		{ 165,0,85 },		//violet red
		{ 10,67,122 },		//twilight blue
		{ 2,3,226 },		//pure blue
		{ 254,47,74 },		//lightish red
		{ 193,74,9 },		//brick orange
		{ 117,8,81 },		//velvet
		{ 255,197,18 },		//sunflower
		{ 166,251,178 },		//light mint green
		{ 154,247,100 },		//light grass green
		{ 139,136,248 },		//lavender blue
		{ 175,47,13 },		//rusty red
		{ 165,82,230 },		//lightish purple
		{ 183,201,226 },		//light blue grey
		{ 113,170,52 },		//leaf
		{ 252,130,74 },		//orangish
		{ 177,210,123 },		//pale olive green
		{ 241,243,63 },		//off yellow
		{ 240,131,58 },		//dusty orange
		{ 255,255,129 },		//butter
		{ 12,23,147 },		//royal
		{ 0,95,106 },		//petrol
		{ 42,254,183 },		//greenish cyan
		{ 195,251,244 },		//duck egg blue
		{ 255,105,175 },		//bubble gum pink
		{ 133,163,178 },		//bluegrey
		{ 150,78,2 },		//warm brown
		{ 78,81,139 },		//twilight
		{ 254,178,9 },		//saffron
		{ 93,33,208 },		//purple/blue
		{ 168,143,89 },		//dark sand
		{ 3,57,248 },		//vibrant blue
		{ 190,174,138 },		//putty
		{ 77,164,9 },		//lawn green
		{ 75,97,19 },		//camouflage green
		{ 254,130,140 },		//blush pink
		{ 110,16,5 },		//reddy brown
		{ 169,3,8 },		//darkish red
		{ 33,195,111 },		//algae green
		{ 207,82,78 },		//dark coral
		{ 65,253,254 },		//bright cyan
		{ 221,214,24 },		//piss yellow
		{ 219,88,86 },		//pastel red
		{ 0,251,176 },		//greenish turquoise
		{ 202,1,71 },		//ruby
		{ 111,124,0 },		//poop green
		{ 254,66,15 },		//orangered
		{ 254,223,8 },		//dandelion
		{ 104,0,24 },		//claret
		{ 254,208,252 },		//pale mauve
		{ 213,23,78 },		//lipstick
		{ 254,134,164 },		//rosa
		{ 171,126,76 },		//tan brown
		{ 117,128,0 },		//shit green
		{ 140,0,52 },		//red wine
		{ 252,134,170 },		//pinky
		{ 96,102,2 },		//mud green
		{ 99,247,180 },		//light greenish blue
		{ 95,158,143 },		//dull teal
		{ 141,94,183 },		//deep lavender
		{ 21,46,255 },		//vivid blue
		{ 167,94,9 },		//raw umber
		{ 182,255,187 },		//light mint
		{ 202,255,251 },		//light light blue
		{ 27,252,6 },		//highlighter green
		{ 126,160,122 },		//greeny grey
		{ 137,160,176 },		//bluey grey
		{ 84,172,104 },		//algae
		{ 92,139,21 },		//sap green
		{ 255,177,154 },		//pale salmon
		{ 79,115,142 },		//metallic blue
		{ 214,255,250 },		//ice
		{ 160,191,22 },		//gross green
		{ 62,130,252 },		//dodger blue
		{ 251,85,129 },		//warm pink
		{ 86,252,162 },		//light green blue
		{ 105,157,76 },		//flat green
		{ 31,59,77 },		//dark blue grey
		{ 178,113,61 },		//clay brown
		{ 252,225,102 },		//sand yellow
		{ 253,89,86 },		//grapefruit
		{ 254,75,3 },		//blood orange
		{ 214,255,254 },		//very pale blue
		{ 199,121,134 },		//old pink
		{ 255,7,58 },		//neon red
		{ 249,188,8 },		//golden rod
		{ 78,5,80 },		//plum purple
		{ 255,229,173 },		//pale peach
		{ 22,212,63 },		//green again
		{ 114,143,2 },		//dark yellow green
		{ 157,2,22 },		//carmine
		{ 1,84,130 },		//deep sea blue
		{ 217,1,102 },		//dark hot pink
		{ 75,87,219 },		//warm blue
		{ 230,242,162 },		//light khaki
		{ 143,174,34 },		//icky green
		{ 35,196,139 },		//greenblue
		{ 115,74,101 },		//dirty purple
		{ 2,27,249 },		//rich blue
		{ 186,158,136 },		//mushroom
		{ 60,115,168 },		//flat blue
		{ 33,71,97 },		//dark slate blue
		{ 89,133,86 },		//dark sage
		{ 255,97,99 },		//coral pink
		{ 8,148,4 },		//true green
		{ 117,25,115 },		//darkish purple
		{ 127,104,78 },		//dark taupe
		{ 149,163,166 },		//cool grey
		{ 253,255,99 },		//canary
		{ 150,180,3 },		//booger green
		{ 209,118,143 },		//muted pink
		{ 142,118,24 },		//hazel
		{ 153,0,250 },		//vivid purple
		{ 172,116,52 },		//leather
		{ 1,192,141 },		//green/blue
		{ 255,218,3 },		//sunflower yellow
		{ 114,0,88 },		//rich purple
		{ 215,103,173 },		//pale magenta
		{ 194,255,137 },		//light yellowish green
		{ 58,24,177 },		//indigo blue
		{ 157,7,89 },		//dark fuchsia
		{ 255,227,110 },		//yellow tan
		{ 32,249,134 },		//wintergreen
		{ 251,95,252 },		//violet pink
		{ 19,187,175 },		//topaz
		{ 120,209,182 },		//seafoam blue
		{ 253,220,92 },		//light gold
		{ 134,161,125 },		//grey/green
		{ 144,253,169 },		//foam green
		{ 255,255,182 },		//creme
		{ 36,122,253 },		//clear blue
		{ 49,102,138 },		//ugly blue
		{ 203,104,67 },		//terracota
		{ 252,246,121 },		//straw
		{ 254,252,175 },		//parchment
		{ 253,185,21 },		//orangey yellow
		{ 113,159,145 },		//greyish teal
		{ 33,56,171 },		//sapphire
		{ 16,122,176 },		//nice blue
		{ 202,107,2 },		//browny orange
		{ 188,245,166 },		//washed out green
		{ 123,242,218 },		//tiffany blue
		{ 160,254,191 },		//light seafoam
		{ 78,253,84 },		//light neon green
		{ 83,254,92 },		//light bright green
		{ 118,253,168 },		//light bluish green
		{ 246,104,142 },		//rosy pink
		{ 255,154,138 },		//peachy pink
		{ 177,252,153 },		//pale light green
		{ 200,127,137 },		//old rose
		{ 99,169,80 },		//fern
		{ 38,83,141 },		//dusk blue
		{ 127,143,78 },		//camo
		{ 183,82,3 },		//burnt siena
		{ 12,220,115 },		//tealish green
		{ 105,131,57 },		//swamp
		{ 203,165,96 },		//sand brown
		{ 139,49,3 },		//rust brown
		{ 253,141,73 },		//orangeish
		{ 58,46,254 },		//light royal blue
		{ 135,95,66 },		//cocoa
		{ 202,155,247 },		//baby purple
		{ 154,98,0 },		//raw sienna
		{ 44,250,31 },		//radioactive green
		{ 196,254,130 },		//light pea green
		{ 172,79,6 },		//cinnamon
		{ 242,171,21 },		//squash
		{ 60,65,66 },		//charcoal grey
		{ 157,255,0 },		//bright yellow green
		{ 182,196,6 },		//baby puke green
		{ 64,253,20 },		//poison green
		{ 239,192,254 },		//light lavendar
		{ 133,14,4 },		//indian red
		{ 255,243,154 },		//dark cream
		{ 199,172,125 },		//toupe
		{ 253,177,71 },		//butterscotch
		{ 104,50,227 },		//burple
		{ 169,190,112 },		//tan green
		{ 255,223,34 },		//sun yellow
		{ 253,222,108 },		//pale gold
		{ 200,255,176 },		//light light green
		{ 143,182,123 },		//lichen
		{ 181,206,8 },		//green/yellow
		{ 29,93,236 },		//azul
		{ 255,249,23 },		//sunny yellow
		{ 208,228,41 },		//sickly yellow
		{ 0,147,55 },		//kelley green
		{ 126,64,113 },		//bruise
		{ 111,108,10 },		//browny green
		{ 107,124,133 },		//battleship grey
		{ 86,132,174 },		//off blue
		{ 255,250,134 },		//manilla
		{ 201,209,121 },		//greenish beige
		{ 218,70,125 },		//darkish pink
		{ 255,253,120 },		//custard
		{ 125,113,3 },		//ugly brown
		{ 80,123,156 },		//stormy blue
		{ 196,142,253 },		//liliac
		{ 173,144,13 },		//baby shit brown
		{ 153,117,112 },		//reddish grey
		{ 255,178,208 },		//powder pink
		{ 67,5,65 },		//eggplant purple
		{ 255,252,196 },		//egg shell
		{ 211,182,131 },		//very light brown
		{ 189,248,163 },		//tea green
		{ 255,111,82 },		//orange pink
		{ 183,225,161 },		//light grey green
		{ 142,229,63 },		//kiwi green
		{ 99,179,101 },		//boring green
		{ 178,251,165 },		//light pastel green
		{ 255,99,233 },		//candy pink
		{ 152,63,178 },		//purply
		{ 148,126,148 },		//purpley grey
		{ 172,134,168 },		//dusty lavender
		{ 204,173,96 },		//desert
		{ 150,110,189 },		//deep lilac
		{ 231,142,165 },		//pig pink
		{ 194,183,9 },		//olive yellow
		{ 167,255,181 },		//light seafoam green
		{ 166,200,117 },		//light moss green
		{ 221,133,215 },		//lavender pink
		{ 8,120,127 },		//deep aqua
		{ 175,168,139 },		//bland
		{ 255,7,137 },		//strong pink
		{ 12,181,119 },		//green teal
		{ 1,115,116 },		//deep turquoise
		{ 31,99,87 },		//dark green blue
		{ 5,255,166 },		//bright sea green
		{ 155,181,60 },		//booger
		{ 83,60,198 },		//blue with a hint of purple
		{ 34,66,199 },		//blue blue
		{ 55,120,191 },		//windows blue
		{ 97,222,42 },		//toxic green
		{ 12,6,247 },		//strong blue
		{ 10,95,56 },		//spruce
		{ 217,155,130 },		//pinkish tan
		{ 239,180,53 },		//macaroni and cheese
		{ 94,155,138 },		//grey teal
		{ 76,144,133 },		//dusty teal
		{ 56,128,4 },		//dark grass green
		{ 165,163,145 },		//cement
		{ 252,252,129 },		//yellowish tan
		{ 149,46,143 },		//warm purple
		{ 101,171,124 },		//tea
		{ 212,255,255 },		//really light blue
		{ 112,178,63 },		//nasty green
		{ 137,69,133 },		//light eggplant
		{ 105,216,79 },		//fresh green
		{ 168,255,4 },		//electric lime
		{ 178,153,110 },		//dust
		{ 86,174,87 },		//dark pastel green
		{ 172,194,217 },		//cloudy blue
	};

}
#endif //DOXYGEN
#endif  //ISPRING_7E1_A_4_RGB_HPP_INCLUDED
