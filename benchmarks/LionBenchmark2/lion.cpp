#include "LionBenchmark.h"

static char g_lion[] =
	"f2cc99\n"
	"M 69,18 L 82,8 L 99,3 L 118,5 L 135,12 L 149,21 L 156,13 L 165,9 L 177,13 L 183,28 L 180,50 L 164,91 L 155,107 L 154,114 L 151,121 L 141,127 L 139,136 L 155,206 L 157,251 L 126,342 L 133,357 L 128,376 L 83,376 L 75,368 L 67,350 L 61,350 L 53,369 L 4,369 L 2,361 L 5,354 L 12,342 L 16,321 L 4,257 L 4,244 L 7,218 L 9,179 L 26,127 L 43,93 L 32,77 L 30,70 L 24,67 L 16,49 L 17,35 L 18,23 L 30,12 L 40,7 L 53,7 L 62,12 L 69,18 L 69,18 L 69,18\n"
	"e5b27f\n"
	"M 142,79 L 136,74 L 138,82 L 133,78 L 133,84 L 127,78 L 128,85 L 124,80 L 125,87 L 119,82 L 119,90 L 125,99 L 125,96 L 128,100 L 128,94 L 131,98 L 132,93 L 135,97 L 136,93 L 138,97 L 139,94 L 141,98 L 143,94 L 144,85 L 142,79 L 142,79 L 142,79\n"
	"eb8080\n"
	"M 127,101 L 132,100 L 137,99 L 144,101 L 143,105 L 135,110 L 127,101 L 127,101 L 127,101\n"
	"f2cc99\n"
	"M 178,229 L 157,248 L 139,296 L 126,349 L 137,356 L 158,357 L 183,342 L 212,332 L 235,288 L 235,261 L 228,252 L 212,250 L 188,251 L 178,229 L 178,229 L 178,229\n"
	"9c826b\n"
	"M 56,229 L 48,241 L 48,250 L 57,281 L 63,325 L 71,338 L 81,315 L 76,321 L 79,311 L 83,301 L 75,308 L 80,298 L 73,303 L 76,296 L 71,298 L 74,292 L 69,293 L 74,284 L 78,278 L 71,278 L 74,274 L 68,273 L 70,268 L 66,267 L 68,261 L 60,266 L 62,259 L 65,253 L 57,258 L 59,251 L 55,254 L 55,248 L 60,237 L 54,240 L 58,234 L 54,236 L 56,229 L 56,229 L 56,229\n"
	"M 74,363 L 79,368 L 81,368 L 85,362 L 89,363 L 92,370 L 96,373 L 101,372 L 108,361 L 110,371 L 113,373 L 116,371 L 120,358 L 122,363 L 123,371 L 126,371 L 129,367 L 132,357 L 135,361 L 130,376 L 127,377 L 94,378 L 84,376 L 76,371 L 74,363 L 74,363 L 74,363\n"
	"M 212,250 L 219,251 L 228,258 L 236,270 L 235,287 L 225,304 L 205,332 L 177,343 L 171,352 L 158,357 L 166,352 L 168,346 L 168,339 L 165,333 L 155,327 L 155,323 L 161,320 L 165,316 L 169,316 L 167,312 L 171,313 L 168,308 L 173,309 L 170,306 L 177,306 L 175,308 L 177,311 L 174,311 L 176,316 L 171,315 L 174,319 L 168,320 L 168,323 L 175,327 L 179,332 L 183,326 L 184,332 L 189,323 L 190,328 L 194,320 L 194,325 L 199,316 L 201,320 L 204,313 L 206,316 L 208,310 L 211,305 L 219,298 L 226,288 L 229,279 L 228,266 L 224,259 L 217,253 L 212,250 L 212,250 L 212,250\n"
	"M 151,205 L 151,238 L 149,252 L 141,268 L 128,282 L 121,301 L 130,300 L 126,313 L 118,324 L 116,337 L 120,346 L 133,352 L 133,340 L 137,333 L 145,329 L 156,327 L 153,319 L 153,291 L 157,271 L 170,259 L 178,277 L 193,250 L 174,216 L 151,205 L 151,205 L 151,205\n"
	"M 78,127 L 90,142 L 95,155 L 108,164 L 125,167 L 139,175 L 150,206 L 152,191 L 141,140 L 121,148 L 100,136 L 78,127 L 78,127 L 78,127\n"
	"M 21,58 L 35,63 L 38,68 L 32,69 L 42,74 L 40,79 L 47,80 L 54,83 L 45,94 L 34,81 L 32,73 L 24,66 L 21,58 L 21,58 L 21,58\n"
	"M 71,34 L 67,34 L 66,27 L 59,24 L 54,17 L 48,17 L 39,22 L 30,26 L 28,31 L 31,39 L 38,46 L 29,45 L 36,54 L 41,61 L 41,70 L 50,69 L 54,71 L 55,58 L 67,52 L 76,43 L 76,39 L 68,44 L 71,34 L 71,34 L 71,34\n"
	"M 139,74 L 141,83 L 143,89 L 144,104 L 148,104 L 155,106 L 154,86 L 157,77 L 155,72 L 150,77 L 144,77 L 139,74 L 139,74 L 139,74\n"
	"M 105,44 L 102,53 L 108,58 L 111,62 L 112,55 L 105,44 L 105,44 L 105,44\n"
	"M 141,48 L 141,54 L 144,58 L 139,62 L 137,66 L 136,59 L 137,52 L 141,48 L 141,48 L 141,48\n"
	"M 98,135 L 104,130 L 105,134 L 108,132 L 108,135 L 112,134 L 113,137 L 116,136 L 116,139 L 119,139 L 124,141 L 128,140 L 133,138 L 140,133 L 139,140 L 126,146 L 104,144 L 98,135 L 98,135 L 98,135\n"
	"M 97,116 L 103,119 L 103,116 L 111,118 L 116,117 L 122,114 L 127,107 L 135,111 L 142,107 L 141,114 L 145,118 L 149,121 L 145,125 L 140,124 L 127,121 L 113,125 L 100,124 L 97,116 L 97,116 L 97,116\n"
	"M 147,33 L 152,35 L 157,34 L 153,31 L 160,31 L 156,28 L 161,28 L 159,24 L 163,25 L 163,21 L 165,22 L 170,23 L 167,17 L 172,21 L 174,18 L 175,23 L 176,22 L 177,28 L 177,33 L 174,37 L 176,39 L 174,44 L 171,49 L 168,53 L 164,57 L 159,68 L 156,70 L 154,60 L 150,51 L 146,43 L 144,35 L 147,33 L 147,33 L 147,33\n"
	"M 85,72 L 89,74 L 93,75 L 100,76 L 105,75 L 102,79 L 94,79 L 88,76 L 85,72 L 85,72 L 85,72\n"
	"M 86,214 L 79,221 L 76,232 L 82,225 L 78,239 L 82,234 L 78,245 L 81,243 L 79,255 L 84,250 L 84,267 L 87,254 L 90,271 L 90,257 L 95,271 L 93,256 L 95,249 L 92,252 L 93,243 L 89,253 L 89,241 L 86,250 L 87,236 L 83,245 L 87,231 L 82,231 L 90,219 L 84,221 L 86,214 L 86,214 L 86,214\n"
	"ffcc7f\n"
	"M 93,68 L 96,72 L 100,73 L 106,72 L 108,66 L 105,63 L 100,62 L 93,68 L 93,68 L 93,68\n"
	"M 144,64 L 142,68 L 142,73 L 146,74 L 150,73 L 154,64 L 149,62 L 144,64 L 144,64 L 144,64\n"
	"9c826b\n"
	"M 57,91 L 42,111 L 52,105 L 41,117 L 53,112 L 46,120 L 53,116 L 50,124 L 57,119 L 55,127 L 61,122 L 60,130 L 67,126 L 66,134 L 71,129 L 72,136 L 77,130 L 76,137 L 80,133 L 82,138 L 86,135 L 96,135 L 94,129 L 86,124 L 83,117 L 77,123 L 79,117 L 73,120 L 75,112 L 68,116 L 71,111 L 65,114 L 69,107 L 63,110 L 68,102 L 61,107 L 66,98 L 61,103 L 63,97 L 57,99 L 57,91 L 57,91 L 57,91\n"
	"M 83,79 L 76,79 L 67,82 L 75,83 L 65,88 L 76,87 L 65,92 L 76,91 L 68,96 L 77,95 L 70,99 L 80,98 L 72,104 L 80,102 L 76,108 L 85,103 L 92,101 L 87,98 L 93,96 L 86,94 L 91,93 L 85,91 L 93,89 L 99,89 L 105,93 L 107,85 L 102,82 L 92,80 L 83,79 L 83,79 L 83,79\n"
	"M 109,77 L 111,83 L 109,89 L 113,94 L 117,90 L 117,81 L 114,78 L 109,77 L 109,77 L 109,77\n"
	"M 122,128 L 127,126 L 134,127 L 136,129 L 134,130 L 130,128 L 124,129 L 122,128 L 122,128 L 122,128\n"
	"M 78,27 L 82,32 L 80,33 L 82,36 L 78,37 L 82,40 L 78,42 L 81,46 L 76,47 L 78,49 L 74,50 L 82,52 L 87,50 L 83,48 L 91,46 L 86,45 L 91,42 L 88,40 L 92,37 L 86,34 L 90,31 L 86,29 L 89,26 L 78,27 L 78,27 L 78,27\n"
	"M 82,17 L 92,20 L 79,21 L 90,25 L 81,25 L 94,28 L 93,26 L 101,30 L 101,26 L 107,33 L 108,28 L 111,40 L 113,34 L 115,45 L 117,39 L 119,54 L 121,46 L 124,58 L 126,47 L 129,59 L 130,49 L 134,58 L 133,44 L 137,48 L 133,37 L 137,40 L 133,32 L 126,20 L 135,26 L 132,19 L 138,23 L 135,17 L 142,18 L 132,11 L 116,6 L 94,6 L 78,11 L 92,12 L 80,14 L 90,16 L 82,17 L 82,17 L 82,17\n"
	"M 142,234 L 132,227 L 124,223 L 115,220 L 110,225 L 118,224 L 127,229 L 135,236 L 122,234 L 115,237 L 113,242 L 121,238 L 139,243 L 121,245 L 111,254 L 95,254 L 102,244 L 104,235 L 110,229 L 100,231 L 104,224 L 113,216 L 122,215 L 132,217 L 141,224 L 145,230 L 149,240 L 142,234 L 142,234 L 142,234\n"
	"M 115,252 L 125,248 L 137,249 L 143,258 L 134,255 L 125,254 L 115,252 L 115,252 L 115,252\n"
	"M 114,212 L 130,213 L 140,219 L 147,225 L 144,214 L 137,209 L 128,207 L 114,212 L 114,212 L 114,212\n"
	"M 102,263 L 108,258 L 117,257 L 131,258 L 116,260 L 109,265 L 102,263 L 102,263 L 102,263\n"
	"M 51,241 L 35,224 L 40,238 L 23,224 L 31,242 L 19,239 L 28,247 L 17,246 L 25,250 L 37,254 L 39,263 L 44,271 L 47,294 L 48,317 L 51,328 L 60,351 L 60,323 L 53,262 L 47,246 L 51,241 L 51,241 L 51,241\n"
	"M 2,364 L 9,367 L 14,366 L 18,355 L 20,364 L 26,366 L 31,357 L 35,364 L 39,364 L 42,357 L 47,363 L 53,360 L 59,357 L 54,369 L 7,373 L 2,364 L 2,364 L 2,364\n"
	"M 7,349 L 19,345 L 25,339 L 18,341 L 23,333 L 28,326 L 23,326 L 27,320 L 23,316 L 25,311 L 20,298 L 15,277 L 12,264 L 9,249 L 10,223 L 3,248 L 5,261 L 15,307 L 17,326 L 11,343 L 7,349 L 7,349 L 7,349\n"
	"M 11,226 L 15,231 L 25,236 L 18,227 L 11,226 L 11,226 L 11,226\n"
	"M 13,214 L 19,217 L 32,227 L 23,214 L 16,208 L 15,190 L 24,148 L 31,121 L 24,137 L 14,170 L 8,189 L 13,214 L 13,214 L 13,214\n"
	"M 202,254 L 195,258 L 199,260 L 193,263 L 197,263 L 190,268 L 196,268 L 191,273 L 188,282 L 200,272 L 194,272 L 201,266 L 197,265 L 204,262 L 200,258 L 204,256 L 202,254 L 202,254 L 202,254\n"
	"845433\n"
	"M 151,213 L 165,212 L 179,225 L 189,246 L 187,262 L 179,275 L 176,263 L 177,247 L 171,233 L 163,230 L 165,251 L 157,264 L 146,298 L 145,321 L 133,326 L 143,285 L 154,260 L 153,240 L 151,213 L 151,213 L 151,213\n"
	"M 91,132 L 95,145 L 97,154 L 104,148 L 107,155 L 109,150 L 111,158 L 115,152 L 118,159 L 120,153 L 125,161 L 126,155 L 133,164 L 132,154 L 137,163 L 137,152 L 142,163 L 147,186 L 152,192 L 148,167 L 141,143 L 124,145 L 105,143 L 91,132 L 91,132 L 91,132\n"
	"9c826b\n"
	"M 31,57 L 23,52 L 26,51 L 20,44 L 23,42 L 21,36 L 22,29 L 25,23 L 24,32 L 30,43 L 26,41 L 30,50 L 26,48 L 31,57 L 31,57 L 31,57\n"
	"M 147,21 L 149,28 L 155,21 L 161,16 L 167,14 L 175,15 L 173,11 L 161,9 L 147,21 L 147,21 L 147,21\n"
	"M 181,39 L 175,51 L 169,57 L 171,65 L 165,68 L 165,75 L 160,76 L 162,91 L 171,71 L 180,51 L 181,39 L 181,39 L 181,39\n"
	"M 132,346 L 139,348 L 141,346 L 142,341 L 147,342 L 143,355 L 133,350 L 132,346 L 132,346 L 132,346\n"
	"M 146,355 L 151,352 L 155,348 L 157,343 L 160,349 L 151,356 L 147,357 L 146,355 L 146,355 L 146,355\n"
	"M 99,266 L 100,281 L 94,305 L 86,322 L 78,332 L 72,346 L 73,331 L 91,291 L 99,266 L 99,266 L 99,266\n"
	"M 20,347 L 32,342 L 45,340 L 54,345 L 45,350 L 42,353 L 38,350 L 31,353 L 29,356 L 23,350 L 19,353 L 15,349 L 20,347 L 20,347 L 20,347\n"
	"M 78,344 L 86,344 L 92,349 L 88,358 L 84,352 L 78,344 L 78,344 L 78,344\n"
	"M 93,347 L 104,344 L 117,345 L 124,354 L 121,357 L 116,351 L 112,351 L 108,355 L 102,351 L 93,347 L 93,347 L 93,347\n"
	"000000\n"
	"M 105,12 L 111,18 L 113,24 L 113,29 L 119,34 L 116,23 L 112,16 L 105,12 L 105,12 L 105,12\n"
	"M 122,27 L 125,34 L 127,43 L 128,34 L 125,29 L 122,27 L 122,27 L 122,27\n"
	"M 115,13 L 122,19 L 122,15 L 113,10 L 115,13 L 115,13 L 115,13\n"
	"ffe5b2\n"
	"M 116,172 L 107,182 L 98,193 L 98,183 L 90,199 L 89,189 L 84,207 L 88,206 L 87,215 L 95,206 L 93,219 L 91,230 L 98,216 L 97,226 L 104,214 L 112,209 L 104,208 L 113,202 L 126,200 L 139,207 L 132,198 L 142,203 L 134,192 L 142,195 L 134,187 L 140,185 L 130,181 L 136,177 L 126,177 L 125,171 L 116,180 L 116,172 L 116,172 L 116,172\n"
	"M 74,220 L 67,230 L 67,221 L 59,235 L 63,233 L 60,248 L 70,232 L 65,249 L 71,243 L 67,256 L 73,250 L 69,262 L 73,259 L 71,267 L 76,262 L 72,271 L 78,270 L 76,275 L 82,274 L 78,290 L 86,279 L 86,289 L 92,274 L 88,275 L 87,264 L 82,270 L 82,258 L 77,257 L 78,247 L 73,246 L 77,233 L 72,236 L 74,220 L 74,220 L 74,220\n"
	"M 133,230 L 147,242 L 148,250 L 145,254 L 138,247 L 129,246 L 142,245 L 138,241 L 128,237 L 137,238 L 133,230 L 133,230 L 133,230\n"
	"M 133,261 L 125,261 L 116,263 L 111,267 L 125,265 L 133,261 L 133,261 L 133,261\n"
	"M 121,271 L 109,273 L 103,279 L 99,305 L 92,316 L 85,327 L 83,335 L 89,340 L 97,341 L 94,336 L 101,336 L 96,331 L 103,330 L 97,327 L 108,325 L 99,322 L 109,321 L 100,318 L 110,317 L 105,314 L 110,312 L 107,310 L 113,308 L 105,306 L 114,303 L 105,301 L 115,298 L 107,295 L 115,294 L 108,293 L 117,291 L 109,289 L 117,286 L 109,286 L 118,283 L 112,281 L 118,279 L 114,278 L 119,276 L 115,274 L 121,271 L 121,271 L 121,271\n"
	"M 79,364 L 74,359 L 74,353 L 76,347 L 80,351 L 83,356 L 82,360 L 79,364 L 79,364 L 79,364\n"
	"M 91,363 L 93,356 L 97,353 L 103,355 L 105,360 L 103,366 L 99,371 L 94,368 L 91,363 L 91,363 L 91,363\n"
	"M 110,355 L 114,353 L 118,357 L 117,363 L 113,369 L 111,362 L 110,355 L 110,355 L 110,355\n"
	"M 126,354 L 123,358 L 124,367 L 126,369 L 129,361 L 129,357 L 126,354 L 126,354 L 126,354\n"
	"M 30,154 L 24,166 L 20,182 L 23,194 L 29,208 L 37,218 L 41,210 L 41,223 L 46,214 L 46,227 L 52,216 L 52,227 L 61,216 L 59,225 L 68,213 L 73,219 L 70,207 L 77,212 L 69,200 L 77,202 L 70,194 L 78,197 L 68,187 L 76,182 L 64,182 L 58,175 L 58,185 L 53,177 L 50,186 L 46,171 L 44,182 L 39,167 L 36,172 L 36,162 L 30,166 L 30,154 L 30,154 L 30,154\n"
	"M 44,130 L 41,137 L 45,136 L 43,150 L 48,142 L 48,157 L 53,150 L 52,164 L 60,156 L 61,169 L 64,165 L 66,175 L 70,167 L 74,176 L 77,168 L 80,183 L 85,172 L 90,182 L 93,174 L 98,181 L 99,173 L 104,175 L 105,169 L 114,168 L 102,163 L 95,157 L 94,166 L 90,154 L 87,162 L 82,149 L 75,159 L 72,148 L 68,155 L 67,143 L 62,148 L 62,138 L 58,145 L 56,133 L 52,142 L 52,128 L 49,134 L 47,125 L 44,130 L 44,130 L 44,130\n"
	"M 13,216 L 19,219 L 36,231 L 22,223 L 16,222 L 22,227 L 12,224 L 13,220 L 16,220 L 13,216 L 13,216 L 13,216\n"
	"M 10,231 L 14,236 L 25,239 L 27,237 L 19,234 L 10,231 L 10,231 L 10,231\n"
	"M 9,245 L 14,242 L 25,245 L 13,245 L 9,245 L 9,245 L 9,245\n"
	"M 33,255 L 26,253 L 18,254 L 25,256 L 18,258 L 27,260 L 18,263 L 27,265 L 19,267 L 29,270 L 21,272 L 29,276 L 21,278 L 30,281 L 22,283 L 31,287 L 24,288 L 32,292 L 23,293 L 34,298 L 26,299 L 37,303 L 32,305 L 39,309 L 33,309 L 39,314 L 34,314 L 40,318 L 34,317 L 40,321 L 34,321 L 41,326 L 33,326 L 40,330 L 33,332 L 39,333 L 33,337 L 42,337 L 54,341 L 49,337 L 52,335 L 47,330 L 50,330 L 45,325 L 49,325 L 45,321 L 48,321 L 45,316 L 46,306 L 45,286 L 43,274 L 36,261 L 33,255 L 33,255 L 33,255\n"
	"M 7,358 L 9,351 L 14,351 L 17,359 L 11,364 L 7,358 L 7,358 L 7,358\n"
	"M 44,354 L 49,351 L 52,355 L 49,361 L 44,354 L 44,354 L 44,354\n"
	"M 32,357 L 37,353 L 40,358 L 36,361 L 32,357 L 32,357 L 32,357\n"
	"M 139,334 L 145,330 L 154,330 L 158,334 L 154,341 L 152,348 L 145,350 L 149,340 L 147,336 L 141,339 L 139,345 L 136,342 L 136,339 L 139,334 L 139,334 L 139,334\n"
	"M 208,259 L 215,259 L 212,255 L 220,259 L 224,263 L 225,274 L 224,283 L 220,292 L 208,300 L 206,308 L 203,304 L 199,315 L 197,309 L 195,318 L 193,313 L 190,322 L 190,316 L 185,325 L 182,318 L 180,325 L 172,321 L 178,320 L 176,313 L 186,312 L 180,307 L 188,307 L 184,303 L 191,302 L 186,299 L 195,294 L 187,290 L 197,288 L 192,286 L 201,283 L 194,280 L 203,277 L 198,275 L 207,271 L 200,269 L 209,265 L 204,265 L 212,262 L 208,259 L 208,259 L 208,259\n"
	"M 106,126 L 106,131 L 109,132 L 111,134 L 115,132 L 115,135 L 119,133 L 118,137 L 123,137 L 128,137 L 133,134 L 136,130 L 136,127 L 132,124 L 118,128 L 112,128 L 106,126 L 106,126 L 106,126\n"
	"M 107,114 L 101,110 L 98,102 L 105,97 L 111,98 L 119,102 L 121,108 L 118,112 L 113,115 L 107,114 L 107,114 L 107,114\n"
	"M 148,106 L 145,110 L 146,116 L 150,118 L 152,111 L 151,107 L 148,106 L 148,106 L 148,106\n"
	"M 80,55 L 70,52 L 75,58 L 63,57 L 72,61 L 57,61 L 67,66 L 57,67 L 62,69 L 54,71 L 61,73 L 54,77 L 63,78 L 53,85 L 60,84 L 56,90 L 69,84 L 63,82 L 75,76 L 70,75 L 77,72 L 72,71 L 78,69 L 72,66 L 81,67 L 78,64 L 82,63 L 80,60 L 86,62 L 80,55 L 80,55 L 80,55\n"
	"M 87,56 L 91,52 L 96,50 L 102,56 L 98,56 L 92,60 L 87,56 L 87,56 L 87,56\n"
	"M 85,68 L 89,73 L 98,76 L 106,74 L 96,73 L 91,70 L 85,68 L 85,68 L 85,68\n"
	"M 115,57 L 114,64 L 111,64 L 115,75 L 122,81 L 122,74 L 126,79 L 126,74 L 131,78 L 130,72 L 133,77 L 131,68 L 126,61 L 119,57 L 115,57 L 115,57 L 115,57\n"
	"M 145,48 L 143,53 L 147,59 L 151,59 L 150,55 L 145,48 L 145,48 L 145,48\n"
	"M 26,22 L 34,15 L 43,10 L 52,10 L 59,16 L 47,15 L 32,22 L 26,22 L 26,22 L 26,22\n"
	"M 160,19 L 152,26 L 149,34 L 154,33 L 152,30 L 157,30 L 155,26 L 158,27 L 157,23 L 161,23 L 160,19 L 160,19 L 160,19\n"
	"000000\n"
	"M 98,117 L 105,122 L 109,122 L 105,117 L 113,120 L 121,120 L 130,112 L 128,108 L 123,103 L 123,99 L 128,101 L 132,106 L 135,109 L 142,105 L 142,101 L 145,101 L 145,91 L 148,101 L 145,105 L 136,112 L 135,116 L 143,124 L 148,120 L 150,122 L 142,128 L 133,122 L 121,125 L 112,126 L 103,125 L 100,129 L 96,124 L 98,117 L 98,117 L 98,117\n"
	"M 146,118 L 152,118 L 152,115 L 149,115 L 146,118 L 146,118 L 146,118\n"
	"M 148,112 L 154,111 L 154,109 L 149,109 L 148,112 L 148,112 L 148,112\n"
	"M 106,112 L 108,115 L 114,116 L 118,114 L 106,112 L 106,112 L 106,112\n"
	"M 108,108 L 111,110 L 116,110 L 119,108 L 108,108 L 108,108 L 108,108\n"
	"M 106,104 L 109,105 L 117,106 L 115,104 L 106,104 L 106,104 L 106,104\n"
	"M 50,25 L 41,26 L 34,33 L 39,43 L 49,58 L 36,51 L 47,68 L 55,69 L 54,59 L 61,57 L 74,46 L 60,52 L 67,42 L 57,48 L 61,40 L 54,45 L 60,36 L 59,29 L 48,38 L 52,30 L 47,32 L 50,25 L 50,25 L 50,25\n"
	"M 147,34 L 152,41 L 155,49 L 161,53 L 157,47 L 164,47 L 158,43 L 168,44 L 159,40 L 164,37 L 169,37 L 164,33 L 169,34 L 165,28 L 170,30 L 170,25 L 173,29 L 175,27 L 176,32 L 173,36 L 175,39 L 172,42 L 172,46 L 168,49 L 170,55 L 162,57 L 158,63 L 155,58 L 153,50 L 149,46 L 147,34 L 147,34 L 147,34\n"
	"M 155,71 L 159,80 L 157,93 L 157,102 L 155,108 L 150,101 L 149,93 L 154,101 L 152,91 L 151,83 L 155,79 L 155,71 L 155,71 L 155,71\n"
	"M 112,78 L 115,81 L 114,91 L 112,87 L 113,82 L 112,78 L 112,78 L 112,78\n"
	"M 78,28 L 64,17 L 58,11 L 47,9 L 36,10 L 28,16 L 21,26 L 18,41 L 20,51 L 23,61 L 33,65 L 28,68 L 37,74 L 36,81 L 43,87 L 48,90 L 43,100 L 40,98 L 39,90 L 31,80 L 30,72 L 22,71 L 17,61 L 14,46 L 16,28 L 23,17 L 33,9 L 45,6 L 54,6 L 65,12 L 78,28 L 78,28 L 78,28\n"
	"M 67,18 L 76,9 L 87,5 L 101,2 L 118,3 L 135,8 L 149,20 L 149,26 L 144,19 L 132,12 L 121,9 L 105,7 L 89,8 L 76,14 L 70,20 L 67,18 L 67,18 L 67,18\n"
	"M 56,98 L 48,106 L 56,103 L 47,112 L 56,110 L 52,115 L 57,113 L 52,121 L 62,115 L 58,123 L 65,119 L 63,125 L 69,121 L 68,127 L 74,125 L 74,129 L 79,128 L 83,132 L 94,135 L 93,129 L 85,127 L 81,122 L 76,126 L 75,121 L 71,124 L 71,117 L 66,121 L 66,117 L 62,117 L 64,112 L 60,113 L 60,110 L 57,111 L 61,105 L 57,107 L 60,101 L 55,102 L 56,98 L 56,98 L 56,98\n"
	"M 101,132 L 103,138 L 106,134 L 106,139 L 112,136 L 111,142 L 115,139 L 114,143 L 119,142 L 125,145 L 131,142 L 135,138 L 140,134 L 140,129 L 143,135 L 145,149 L 150,171 L 149,184 L 145,165 L 141,150 L 136,147 L 132,151 L 131,149 L 126,152 L 125,150 L 121,152 L 117,148 L 111,152 L 110,148 L 105,149 L 104,145 L 98,150 L 96,138 L 94,132 L 94,130 L 98,132 L 101,132 L 101,132 L 101,132\n"
	"M 41,94 L 32,110 L 23,132 L 12,163 L 6,190 L 7,217 L 5,236 L 3,247 L 9,230 L 12,211 L 12,185 L 18,160 L 26,134 L 35,110 L 43,99 L 41,94 L 41,94 L 41,94\n"
	"M 32,246 L 41,250 L 50,257 L 52,267 L 53,295 L 53,323 L 59,350 L 54,363 L 51,365 L 44,366 L 42,360 L 40,372 L 54,372 L 59,366 L 62,353 L 71,352 L 75,335 L 73,330 L 66,318 L 68,302 L 64,294 L 67,288 L 63,286 L 63,279 L 59,275 L 58,267 L 56,262 L 50,247 L 42,235 L 44,246 L 32,236 L 35,244 L 32,246 L 32,246 L 32,246\n"
	"M 134,324 L 146,320 L 159,322 L 173,327 L 179,337 L 179,349 L 172,355 L 158,357 L 170,350 L 174,343 L 170,333 L 163,328 L 152,326 L 134,329 L 134,324 L 134,324 L 134,324\n"
	"M 173,339 L 183,334 L 184,338 L 191,329 L 194,332 L 199,323 L 202,325 L 206,318 L 209,320 L 213,309 L 221,303 L 228,296 L 232,289 L 234,279 L 233,269 L 230,262 L 225,256 L 219,253 L 208,252 L 198,252 L 210,249 L 223,250 L 232,257 L 237,265 L 238,277 L 238,291 L 232,305 L 221,323 L 218,335 L 212,342 L 200,349 L 178,348 L 173,339 L 173,339 L 173,339\n"
	"M 165,296 L 158,301 L 156,310 L 156,323 L 162,324 L 159,318 L 162,308 L 162,304 L 165,296 L 165,296 L 165,296\n"
	"M 99,252 L 105,244 L 107,234 L 115,228 L 121,228 L 131,235 L 122,233 L 113,235 L 109,246 L 121,239 L 133,243 L 121,243 L 110,251 L 99,252 L 99,252 L 99,252\n"
	"M 117,252 L 124,247 L 134,249 L 136,253 L 126,252 L 117,252 L 117,252 L 117,252\n"
	"M 117,218 L 132,224 L 144,233 L 140,225 L 132,219 L 117,218 L 117,218 L 117,218\n"
	"M 122,212 L 134,214 L 143,221 L 141,213 L 132,210 L 122,212 L 122,212 L 122,212\n"
	"M 69,352 L 70,363 L 76,373 L 86,378 L 97,379 L 108,379 L 120,377 L 128,378 L 132,373 L 135,361 L 133,358 L 132,366 L 127,375 L 121,374 L 121,362 L 119,367 L 117,374 L 110,376 L 110,362 L 107,357 L 106,371 L 104,375 L 97,376 L 90,375 L 90,368 L 86,362 L 83,364 L 86,369 L 85,373 L 78,370 L 73,362 L 71,351 L 69,352 L 69,352 L 69,352\n"
	"M 100,360 L 96,363 L 99,369 L 102,364 L 100,360 L 100,360 L 100,360\n"
	"M 115,360 L 112,363 L 114,369 L 117,364 L 115,360 L 115,360 L 115,360\n"
	"M 127,362 L 125,364 L 126,369 L 128,365 L 127,362 L 127,362 L 127,362\n"
	"M 5,255 L 7,276 L 11,304 L 15,320 L 13,334 L 6,348 L 2,353 L 0,363 L 5,372 L 12,374 L 25,372 L 38,372 L 44,369 L 42,367 L 36,368 L 31,369 L 30,360 L 27,368 L 20,370 L 16,361 L 15,368 L 10,369 L 3,366 L 3,359 L 6,352 L 11,348 L 17,331 L 19,316 L 12,291 L 9,274 L 5,255 L 5,255 L 5,255\n"
	"M 10,358 L 7,362 L 10,366 L 11,362 L 10,358 L 10,358 L 10,358\n"
	"M 25,357 L 22,360 L 24,366 L 27,360 L 25,357 L 25,357 L 25,357\n"
	"M 37,357 L 34,361 L 36,365 L 38,361 L 37,357 L 37,357 L 37,357\n"
	"M 49,356 L 46,359 L 47,364 L 50,360 L 49,356 L 49,356 L 49,356\n"
	"M 130,101 L 132,102 L 135,101 L 139,102 L 143,103 L 142,101 L 137,100 L 133,100 L 130,101 L 130,101 L 130,101\n"
	"M 106,48 L 105,52 L 108,56 L 109,52 L 106,48 L 106,48 L 106,48\n"
	"M 139,52 L 139,56 L 140,60 L 142,58 L 141,56 L 139,52 L 139,52 L 139,52\n"
	"M 25,349 L 29,351 L 30,355 L 33,350 L 37,348 L 42,351 L 45,347 L 49,345 L 44,343 L 36,345 L 25,349 L 25,349 L 25,349\n"
	"M 98,347 L 105,351 L 107,354 L 109,349 L 115,349 L 120,353 L 118,349 L 113,346 L 104,346 L 98,347 L 98,347 L 98,347\n"
	"M 83,348 L 87,352 L 87,357 L 89,351 L 87,348 L 83,348 L 83,348 L 83,348\n"
	"M 155,107 L 163,107 L 170,107 L 186,108 L 175,109 L 155,109 L 155,107 L 155,107 L 155,107\n"
	"M 153,114 L 162,113 L 175,112 L 192,114 L 173,114 L 154,115 L 153,114 L 153,114 L 153,114\n"
	"M 152,118 L 164,120 L 180,123 L 197,129 L 169,123 L 151,120 L 152,118 L 152,118 L 152,118\n"
	"M 68,109 L 87,106 L 107,106 L 106,108 L 88,108 L 68,109 L 68,109 L 68,109\n"
	"M 105,111 L 95,112 L 79,114 L 71,116 L 85,115 L 102,113 L 105,111 L 105,111 L 105,111\n"
	"M 108,101 L 98,99 L 87,99 L 78,99 L 93,100 L 105,102 L 108,101 L 108,101 L 108,101\n"
	"M 85,63 L 91,63 L 97,60 L 104,60 L 108,62 L 111,69 L 112,75 L 110,74 L 108,71 L 103,73 L 106,69 L 105,65 L 103,64 L 103,67 L 102,70 L 99,70 L 97,66 L 94,67 L 97,72 L 88,67 L 84,66 L 85,63 L 85,63 L 85,63\n"
	"M 140,74 L 141,66 L 144,61 L 150,61 L 156,62 L 153,70 L 150,73 L 152,65 L 150,65 L 151,68 L 149,71 L 146,71 L 144,66 L 143,70 L 143,74 L 140,74 L 140,74 L 140,74\n"
	"M 146,20 L 156,11 L 163,9 L 172,9 L 178,14 L 182,18 L 184,32 L 182,42 L 182,52 L 177,58 L 176,67 L 171,76 L 165,90 L 157,105 L 160,92 L 164,85 L 168,78 L 167,73 L 173,66 L 172,62 L 175,59 L 174,55 L 177,53 L 180,46 L 181,29 L 179,21 L 173,13 L 166,11 L 159,13 L 153,18 L 148,23 L 146,20 L 146,20 L 146,20\n"
	"M 150,187 L 148,211 L 150,233 L 153,247 L 148,267 L 135,283 L 125,299 L 136,292 L 131,313 L 122,328 L 122,345 L 129,352 L 133,359 L 133,367 L 137,359 L 148,356 L 140,350 L 131,347 L 129,340 L 132,332 L 140,328 L 137,322 L 140,304 L 154,265 L 157,244 L 155,223 L 161,220 L 175,229 L 186,247 L 185,260 L 176,275 L 178,287 L 185,277 L 188,261 L 196,253 L 189,236 L 174,213 L 150,187 L 150,187 L 150,187\n"
	"M 147,338 L 142,341 L 143,345 L 141,354 L 147,343 L 147,338 L 147,338 L 147,338\n"
	"M 157,342 L 156,349 L 150,356 L 157,353 L 163,346 L 162,342 L 157,342 L 157,342 L 157,342\n"
	"M 99,265 L 96,284 L 92,299 L 73,339 L 73,333 L 87,300 L 99,265 L 99,265 L 99,265\n";

struct ColorPolygon : Moveable<ColorPolygon> {
	Vector<Pointf> point;
	Color          color;
};

Vector<ColorPolygon> Lion()
{
	Vector<ColorPolygon> data;
	Color color;
	CParser p(g_lion);
	while(!p.IsEof())
		if(p.Char('M')) {
			data.Add().color = color;
			goto line;
		}
		else
		if(p.Char('L')) {
		line:
			double x = p.ReadDouble();
			p.Char(',');
			double y = p.ReadDouble();
			data.Top().point.Add(Pointf(x, y));
		}
		else {
			dword c = p.ReadNumber(16);
			color = Color(c >> 16, (c >> 8) & 255, c & 255);
		}
	return data;
}

Sizef GetLionSize()
{
	Sizef sz(0, 0);
	static Vector<ColorPolygon> l = Lion();
	for(int i = 0; i < l.GetCount(); i++) {
		Vector<Pointf>& p = l[i].point;
		for(int j = 1; j < p.GetCount(); j++) {
			sz.cx = max(sz.cx, p[j].x);
			sz.cy = max(sz.cy, p[j].y);
		}
	}
	return sz;
}

void PaintLion(Painter& sw)
{
	static Vector<ColorPolygon> l = Lion();
	for(int i = 0; i < l.GetCount(); i++) {
		Vector<Pointf>& p = l[i].point;
		sw.Move(p[0].x, p[0].y);
		for(int j = 1; j < p.GetCount(); j++)
			sw.Line(p[j].x, p[j].y);
//		sw.Stroke(2, l[i].color);
		sw.Fill(l[i].color);
	}
}

INITBLOCK {
	NilPainter p;
	PaintLion(p);
}