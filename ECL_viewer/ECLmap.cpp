#include "ECLmap.h"

static const InsFormat th10_fmts[] = {
    { 0, "" },
    { 1, "" },
    { 10, "" },
    { 11, "m*D" },
    { 12, "ot" },
    { 13, "ot" },
    { 14, "ot" },
    { 15, "m*D" },
    { 16, "mS*D" },
    { 17, "S" },
    { 21, "" },
    { 40, "S" },
    { 42, "S" },
    { 43, "S" },
    { 44, "f" },
    { 45, "f" },
    { 50, "" },
    { 51, "" },
    { 52, "" },
    { 53, "" },
    { 54, "" },
    { 55, "" },
    { 56, "" },
    { 57, "" },
    { 58, "" },
    { 59, "" },
    { 60, "" },
    { 61, "" },
    { 62, "" },
    { 63, "" },
    { 64, "" },
    { 65, "" },
    { 66, "" },
    { 67, "" },
    { 68, "" },
    { 69, "" },
    { 70, "" },
    { 71, "" },
    { 72, "" },
    { 73, "" },
    { 74, "" },
    { 75, "" },
    { 76, "" },
    { 77, "" },
    { 78, "S" },
    { 79, "" },
    { 80, "" },
    { 81, "ffff" },
    { 82, "f" },
    { 83, "S" },
    { 84, "" },
    { 85, "" },
    { 86, "fff" },
    { 87, "fffff" },
    { 88, "" },
    { 89, "SSS" },
    { 256, "mffSSS" },
    { 257, "mffSSS" },
    { 258, "S" },
    { 259, "SS" },
    { 260, "mffSSS" },
    { 261, "mffSSS" },
    { 262, "SS" },
    { 263, "SS" },
    { 264, "SS" },
    { 265, "mffSSS" },
    { 266, "mffSSS" },
    { 267, "mffSSS" },
    { 268, "mffSSS" },
    { 269, "S" },
    { 270, "mffSSSS" },
    { 271, "mffSSSS" },
    { 272, "SS" },
    { 273, "SSf" },
    { 280, "ff" },
    { 281, "SSff" },
    { 282, "ff" },
    { 283, "SSfS" },
    { 284, "ff" },
    { 285, "SSff" },
    { 286, "ff" },
    { 287, "SSff" },
    { 288, "ffff" },
    { 290, "ffff" },
    { 291, "SSfffS" },
    { 292, "SSf" },
    { 293, "SSf" },
    { 294, "" },
    { 295, "" },
    { 296, "SSf" },
    { 297, "ff" },
    { 298, "ff" },
    { 299, "ff" },
    { 320, "ff" },
    { 321, "ff" },
    { 322, "S" },
    { 323, "S" },
    { 324, "ffff" },
    { 325, "" },
    { 326, "" },
    { 327, "SS" },
    { 328, "ff" },
    { 329, "" },
    { 330, "S" },
    { 331, "S" },
    { 332, "S" },
    { 333, "" },
    { 334, "SSSm" },
    { 335, "S" },
    { 336, "S" },
    { 337, "SSS" },
    { 338, "S" },
    { 339, "" },
    { 340, "" },
    { 341, "Sm" },
    { 342, "SSSx" },
    { 343, "" },
    { 344, "S" },
    { 345, "" },
    { 346, "f" },
    { 347, "SfS" },
    { 348, "SSSx" },
    { 349, "ffff" },
    { 350, "ffffff" },
    { 351, "fff" },
    { 352, "SSSS" },
    { 353, "SSSSSS" },
    { 354, "SSS" },
    { 355, "SSSSS" },
    { 356, "fffff" },
    { 357, "SSSx" },
    { 358, "SSSx" },
    { 359, "SSSx" },
    { 360, "S" },
    { 361, "S" },
    { 362, "" },
    { 363, "" },
    { 364, "S" },
    { 365, "" },
    { 366, "SS" },
    { 367, "f" },
    { 368, "SSSS" },
    { 400, "S" },
    { 401, "S" },
    { 402, "SSS" },
    { 403, "Sff" },
    { 404, "Sff" },
    { 405, "Sff" },
    { 406, "SSS" },
    { 407, "SS" },
    { 408, "SSS" },
    { 409, "SSSSSSff" },
    { 410, "" },
    { 411, "SS" },
    { 412, "SSffffSf" },
    { 413, "SSSfffSSSSfS" },
    { 414, "Sff" },
    { 415, "Sff" },
    { 416, "Sf" },
    { 417, "Sf" },
    { 418, "Sf" },
    { 419, "Sf" },
    { 420, "f" },
    { 421, "f" },
    { 422, "Sffffff" },
    { 423, "Sffffffffff" },
    { 424, "Sffff" },
    { 425, "SSSSSSS" },
    { 426, "SSSSSSSSSSS" },
    { 427, "SSSSS" },
    { 428, "SSffSfSf" },
    { 429, "SSSfffSSSSfS" },
    { 430, "Sff" },
    { 431, "SSffSfff" },
    { 432, "SSSfffSSSSfS" },
    { 433, "SSffSfff" },
    { 434, "SSSfffSSSSfS" },
    { 435, "Sffffffff" },
    { 436, "SSSSSSSSS" },
    { -1, NULL }
};

static const InsFormat alcostg_fmts[] = {
    { 16, "mS*D" },
    { 274, "SS" },
    { 275, "SS" },
    { 300, "ffffff" },
    { 301, "ffffff" },
    { 302, "ffffff" },
    { 303, "ffffff" },
    { 369, "SSSS" },
    { 408, "SSS" },
    { 437, "S" },
    { 438, "SS" },
    { 441, "S" },
    { 442, "S" },
    { 443, "S" },
    { 444, "Sf" },
    { -1, NULL }
};

static const InsFormat th11_fmts[] = {
    { 276, "" },
    { 277, "ff" },
    { 278, "S" },
    { 289, "SSfff" },
    { 291, "SSffS" },
    { 305, "Sffffff" },
    { 306, "Sffffff" },
    { 307, "" },
    { 369, "S" },
    { 370, "S" },
    { 371, "S" },
    { 437, "Sff" },
    { 438, "Sf" },
    { 439, "Sff" },
    { 440, "fS" },
    { 441, "S" },
    { 442, "S" },
    { 443, "S" },
    { 444, "S" },
    { 445, "S" },
    { 447, "f" },
    { 448, "S" },
    { 449, "S" },
    { 450, "S" },
    { 500, "S" },
    { -1, NULL }
};

static const InsFormat th12_fmts[] = {
    { 0, "" },
    { 1, "" },
    { 10, "" },
    { 11, "m*D" },
    { 12, "ot" },
    { 13, "ot" },
    { 14, "ot" },
    { 15, "m*D" },
    { 16, "mS*D" },
    { 17, "S" },
    { 21, "" },
    { 40, "S" },
    { 42, "S" },
    { 43, "S" },
    { 44, "f" },
    { 45, "f" },
    { 50, "" },
    { 51, "" },
    { 52, "" },
    { 53, "" },
    { 54, "" },
    { 55, "" },
    { 56, "" },
    { 57, "" },
    { 58, "" },
    { 59, "" },
    { 60, "" },
    { 61, "" },
    { 63, "" },
    { 64, "" },
    { 65, "" },
    { 66, "" },
    { 67, "" },
    { 68, "" },
    { 69, "" },
    { 70, "" },
    { 71, "" },
    { 72, "" },
    { 73, "" },
    { 74, "" },
    { 75, "" },
    { 76, "" },
    { 77, "" },
    { 78, "S" },
    { 79, "" },
    { 80, "" },
    { 81, "ffff" },
    { 82, "f" },
    { 83, "S" },
    { 84, "" },
    { 85, "" },
    { 86, "fff" },
    { 87, "fffff" },
    { 88, "" },
    { 89, "fff" },
    { 256, "mffSSS" },
    { 257, "mffSSS" },
    { 258, "S" },
    { 259, "SS" },
    { 260, "mffSSS" },
    { 261, "mffSSS" },
    { 262, "SS" },
    { 263, "SS" },
    { 264, "SS" },
    { 265, "mffSSS" },
    { 266, "mffSSS" },
    { 267, "mffSSS" },
    { 268, "mffSSS" },
    { 269, "S" },
    { 270, "mffSSSS" },
    { 271, "mffSSSS" },
    { 272, "SS" },
    { 273, "SSf" },
    { 274, "SS" },
    { 275, "SS" },
    { 276, "" },
    { 277, "Sf" },
    { 278, "Sff" },
    { 279, "Sff" },
    { 280, "mSSSSS" },
    { 281, "SS" },
    { 300, "ff" },
    { 301, "SSff" },
    { 302, "ff" },
    { 303, "SSff" },
    { 304, "ff" },
    { 305, "SSff" },
    { 306, "ff" },
    { 307, "SSff" },
    { 308, "ffff" },
    { 309, "SSfff" },
    { 310, "ffff" },
    { 311, "SSfff" },
    { 312, "SSf" },
    { 313, "SSf" },
    { 314, "" },
    { 315, "" },
    { 316, "ff" },
    { 317, "fff" },
    { 318, "ff" },
    { 319, "ff" },
    { 320, "ffffff" },
    { 321, "SSfffff" },
    { 322, "ffffff" },
    { 323, "SSfffff" },
    { 324, "S" },
    { 325, "Sffffff" },
    { 326, "Sffffff" },
    { 327, "" },
    { 328, "ff" },
    { 329, "Sfff" },
    { 330, "ff" },
    { 331, "SSff" },
    { 400, "ff" },
    { 401, "ff" },
    { 402, "S" },
    { 403, "S" },
    { 404, "ffff" },
    { 405, "" },
    { 406, "" },
    { 407, "SS" },
    { 408, "ff" },
    { 409, "" },
    { 410, "S" },
    { 411, "S" },
    { 412, "S" },
    { 413, "" },
    { 414, "SSSm" },
    { 415, "S" },
    { 416, "S" },
    { 417, "SSS" },
    { 418, "S" },
    { 419, "" },
    { 420, "" },
    { 421, "Sm" },
    { 422, "SSSx" },
    { 423, "" },
    { 424, "S" },
    { 425, "" },
    { 426, "f" },
    { 427, "SfS" },
    { 428, "SSSx" },
    { 429, "ffff" },
    { 430, "ffffff" },
    { 431, "fff" },
    { 432, "SSSS" },
    { 433, "SSSSSS" },
    { 434, "SSS" },
    { 435, "SSSSS" },
    { 436, "fffff" },
    { 437, "SSSx" },
    { 438, "SSSx" },
    { 439, "SSSx" },
    { 440, "S" },
    { 440, "S" },
    { 442, "" },
    { 443, "" },
    { 444, "S" },
    { 445, "" },
    { 446, "Sf" },
    { 447, "f" },
    { 448, "SSSS" },
    { 449, "S" },
    { 450, "S" },
    { 451, "S" },
    { 452, "f" },
    { 453, "S" },
    { 454, "" },
    { 455, "SS" },
    { 456, "ffS" },
    { 500, "S" },
    { 501, "S" },
    { 502, "SSS" },
    { 503, "Sff" },
    { 504, "Sff" },
    { 505, "Sff" },
    { 506, "SSS" },
    { 507, "SS" },
    { 508, "SSS" },
    { 509, "SSSSSSff" },
    { 510, "" },
    { 511, "SS" },
    { 512, "f" },
    { 513, "f" },
    { 514, "Sffffff" },
    { 515, "Sffffffffff" },
    { 516, "Sffff" },
    { 517, "SSSSSSS" },
    { 518, "SSSSSSSSSSS" },
    { 519, "SSSSS" },
    { 520, "fff" },
    { 521, "Sffffffff" },
    { 522, "SSSSSSSSS" },
    { 523, "Sff" },
    { 524, "Sf" },
    { 525, "Sff" },
    { 526, "fS" },
    { 527, "" },
    { 528, "" },
    { 529, "S" },
    { 530, "S" },
    { 531, "S" },
    { 532, "f" },
    { 533, "f" },
    { 534, "S" },
    { 535, "S" },
    { 600, "Sffff" },
    { 601, "SSSSSS" },
    { 602, "S" },
    { 603, "SS" },
    { 604, "Sff" },
    { 605, "Sff" },
    { 606, "Sf" },
    { 607, "Sf" },
    { 608, "Sf" },
    { 609, "Sf" },
    { 610, "S" },
    { 611, "S" },
    { 700, "S" },
    { -1, NULL }
};

static const InsFormat th125_fmts[] = {
    { 30, "m*D" },
    { 62, "" },
    { 77, "" },
    { 79, "" },
    { 80, "" },
    { 85, "" },
    { 88, "" },
    { 90, "fffff" },
    { 91, "SfSSff" },
    { 282, "SS" },
    { 303, "SSfS" },
    { 306, "fS" },
    { 307, "SSff" },
    { 318, "Sf" },
    { 322, "fffSfS" },
    { 327, "" },
    { 333, "S" },
    { 426, "f" },
    { 457, "" },
    { 458, "S" },
    { 459, "S" },
    { 460, "f" },
    { 461, "f" },
    { 462, "S" },
    { 463, "m" },
    { 532, "f" },
    { 536, "S" },
    { 604, "SSf" },
    { 609, "Sf" },
    { 612, "ff" },
    { -1, NULL }
};

static const InsFormat th128_fmts[] = {
    { 22, "Sm" },
    { 71, "" },
    { 283, "ffS" },
    { 537, "fSfSSSffffff" },
    { 538, "SSm" },
    { 613, "S" },
    { 614, "fS" },
    { 615, "SS" },
    { -1, NULL }
};

static const InsFormat th13_fmts[] = {
    { 0, "" },
    { 1, "" },
    { 10, "" },
    { 11, "m*D" },
    { 12, "ot" },
    { 13, "ot" },
    { 14, "ot" },
    { 15, "m*D" },
    { 16, "mS*D" },
    { 17, "S" },
    { 18, "S" },
    { 19, "S" },
    { 20, "SS" },
    { 21, "" },
    { 22, "Sm" },
    { 23, "S" },
    { 24, "f" },
    { 30, "m*D" },
    { 40, "S" },
    { 42, "S" },
    { 43, "S" },
    { 44, "f" },
    { 45, "f" },
    { 50, "" },
    { 51, "" },
    { 52, "" },
    { 53, "" },
    { 54, "" },
    { 55, "" },
    { 56, "" },
    { 57, "" },
    { 58, "" },
    { 59, "" },
    { 60, "" },
    { 61, "" },
    { 62, "" },
    { 63, "" },
    { 65, "" },
    { 64, "" },
    { 66, "" },
    { 67, "" },
    { 68, "" },
    { 69, "" },
    { 70, "" },
    { 71, "" },
    { 72, "" },
    { 73, "" },
    { 74, "" },
    { 75, "" },
    { 76, "" },
    { 77, "" },
    { 78, "S" },
    { 81, "ffff" },
    { 82, "f" },
    { 83, "" },
    { 84, "" },
    { 85, "fff" },
    { 86, "fff" },
    { 87, "fffff" },
    { 88, "fffff" },
    { 89, "fff" },
    { 90, "fffff" },
    { 91, "SfSSff" },
    { 92, "SfSSff" },
    { 93, "ffff" },
    { 300, "mffSSS" },
    { 301, "mffSSS" },
    { 302, "S" },
    { 303, "SS" },
    { 304, "mffSSS" },
    { 305, "mffSSS" },
    { 306, "SS" },
    { 307, "SS" },
    { 308, "SS" },
    { 309, "mffSSS" },
    { 310, "mffSSS" },
    { 311, "mffSSS" },
    { 312, "mffSSS" },
    { 313, "S" },
    { 314, "SS" },
    { 315, "SSf" },
    { 316, "SS" },
    { 317, "SS" },
    { 318, "" },
    { 319, "Sf" },
    { 320, "Sff" },
    { 321, "mSSSSS" },
    { 322, "SS" },
    { 323, "SS" },
    { 324, "S" },
    { 325, "SSSS" },
    { 326, "SSSSSS" },
    { 327, "SS" },
    { 328, "SSSS" },
    { 329, "Sff" },
    { 330, "SSSff" },
    { 331, "SS" },
    { 332, "SSSS" },
    { 333, "SSSff" },
    { 334, "S" },
    { 335, "Sff" },
    { 400, "ff" },
    { 401, "SSff" },
    { 402, "ff" },
    { 403, "SSff" },
    { 404, "ff" },
    { 405, "SSff" },
    { 406, "ff" },
    { 407, "SSff" },
    { 408, "ffff" },
    { 409, "SSfff" },
    { 410, "ffff" },
    { 411, "SSfff" },
    { 412, "SSf" },
    { 413, "SSf" },
    { 414, "" },
    { 415, "" },
    { 416, "fff" },
    { 417, "fff" },
    { 418, "ff" },
    { 419, "ff" },
    { 420, "ffffff" },
    { 421, "SSfffff" },
    { 422, "ffffff" },
    { 423, "SSfffff" },
    { 424, "S" },
    { 425, "Sffffff" },
    { 426, "Sffffff" },
    { 427, "" },
    { 428, "ff" },
    { 429, "SSff" },
    { 430, "ff" },
    { 431, "SSff" },
    { 432, "S" },
    { 433, "S" },
    { 434, "SSSff" },
    { 435, "SSSff" },
    { 436, "SSff" },
    { 437, "SSff" },
    { 438, "SSSff" },
    { 439, "SSSff" },
    { 500, "ff" },
    { 501, "ff" },
    { 502, "S" },
    { 503, "S" },
    { 504, "ffff" },
    { 505, "" },
    { 506, "" },
    { 507, "SS" },
    { 508, "ff" },
    { 509, "" },
    { 510, "S" },
    { 511, "S" },
    { 512, "S" },
    { 513, "" },
    { 514, "SSSm" },
    { 515, "S" },
    { 516, "S" },
    { 517, "SSS" },
    { 518, "S" },
    { 519, "" },
    { 520, "" },
    { 521, "Sm" },
    { 522, "SSSx" },
    { 523, "" },
    { 524, "S" },
    { 525, "" },
    { 526, "f" },
    { 527, "SfS" },
    { 528, "SSSx" },
    { 529, "ffff" },
    { 530, "ffffff" },
    { 531, "fff" },
    { 532, "SSSS" },
    { 533, "SSSSSS" },
    { 534, "SSS" },
    { 535, "SSSSS" },
    { 536, "fffff" },
    { 537, "SSSx" },
    { 538, "SSSx" },
    { 539, "SSSx" },
    { 540, "S" },
    { 541, "S" },
    { 542, "" },
    { 543, "" },
    { 544, "S" },
    { 545, "" },
    { 546, "SS" },
    { 547, "f" },
    { 548, "SSSS" },
    { 549, "S" },
    { 550, "S" },
    { 551, "S" },
    { 552, "S" },
    { 553, "S" },
    { 554, "" },
    { 555, "SS" },
    { 556, "m" },
    { 557, "SSSff" },
    { 558, "S" },
    { 559, "S" },
    { 560, "ff" },
    { 561, "" },
    { 562, "" },
    { 600, "S" },
    { 601, "S" },
    { 602, "SSS" },
    { 603, "Sff" },
    { 604, "Sff" },
    { 605, "Sff" },
    { 606, "SSS" },
    { 607, "SS" },
    { 608, "SSS" },
    { 609, "SSSSSSff" },
    { 610, "SSSSSSSSffff" },
    { 611, "SSSSSff" },
    { 612, "SSSSSSSffff" },
    { 613, "" },
    { 614, "SS" },
    { 615, "f" },
    { 616, "f" },
    { 617, "Sffffff" },
    { 618, "Sffffffffff" },
    { 619, "Sffff" },
    { 620, "SSSSSSS" },
    { 621, "SSSSSSSSSSS" },
    { 622, "SSSSS" },
    { 623, "fff" },
    { 624, "Sffffffff" },
    { 625, "SSSSSSSSS" },
    { 626, "Sff" },
    { 627, "Sf" },
    { 628, "Sff" },
    { 629, "fS" },
    { 630, "S" },
    { 631, "S" },
    { 632, "S" },
    { 633, "S" },
    { 634, "S" },
    { 635, "f" },
    { 636, "f" },
    { 637, "S" },
    { 638, "S" },
    { 639, "S" },
    { 640, "SSm" },
    { 700, "Sffff" },
    { 701, "SSSSSS" },
    { 702, "S" },
    { 703, "SS" },
    { 704, "Sff" },
    { 705, "Sff" },
    { 706, "Sf" },
    { 707, "Sf" },
    { 708, "Sf" },
    { 709, "Sf" },
    { 710, "S" },
    { 711, "S" },
    { 712, "ff" },
    { 713, "S" },
    { 714, "SS" },
    { 800, "Sm" },
    { 801, "ffS" },
    { 802, "S" },
    { 900, "S" },
    { 1000, "S" },
    { 1001, "S" },
    { 1002, "S" },
    { 1003, "S" },
    { -1, NULL }
};

/* Inherits th13_fmts */
static const InsFormat th14_fmts[] = {
    { 336, "SS" },
    { 337, "SSfff" },
    { 440, "f" },
    { 441, "SSf" },
    { 442, "f" },
    { 443, "SSf" },
    { 444, "f" },
    { 445, "SSf" },
    { 446, "f" },
    { 447, "SSf" },
    { 563, "S" },
    { 564, "f" },
    { 565, "f" },
    { 566, "" },
    { 567, "S" },
    { 568, "S" },
    { 641, "S" },
    { 901, "" },
    { 902, "" },
    { -1, NULL }
};

static const InsFormat th143_fmts[] = {
    { 1004, "" },
    { 1005, "" },
    { 1006, "" },
    { -1, NULL }
};

static const InsFormat th15_fmts[] = {
    { 569, "S" },
    { 570, "" },
    { 571, "" },
    { -1, NULL }
};

static const InsFormat th16_fmts[] = {
    { 337, "SS" },
    { 338, "SSfff" },
    { 339, "SSS" },
    { 340, "S" },
    { 572, "S" },
    { 1000, "SSS" },
    { -1, NULL }
};

static const InsFormat th165_fmts[] = {
    { 1000, "" },
    { 1001, "" },
    { 1002, "f" },
    { 1005, "S" },
    { 1006, "f" },
    { 1007, "S" },
    { 1008, "S" },
    { 1009, "S" },
    { 1010, "f" },
    { 1011, "S" },
    { 1012, "S" },
    { 1013, "" },
    { 1014, "S" },
    { -1, NULL }
};

static const InsFormat th17_fmts[] = {
    { 904, "f" },
    { 1001, "S"},
    { -1, NULL }
};

static const InsFormat th18_fmts[] = {
    { 94, "ffffff" },
    { 573, "SS" },
    { 574, "S" },
    { -1, NULL }
};

static const InsFormat th185_fmts[] = {
    { 535, "SSSSSSSSS" },
    { 536, "fffffffff" },
    { 1001, "S" },
    { 1002, "" },
    { 1003, "" },
    { 1004, "S" },
    { 1005, "" },
    { 1006, "m" },
    { 1008, "" },
    { 1009, "" },
    { 1010, ""},
    { 1011, "SS" },
    { 1013, "SSSSSSSSS" },
    { 1015, "SS" },
    { 1017, "" },
    { 1018, "S" },
    { 1019, "" },
    { 1020, "S" },
    { 1021, "SS" },
    { 1022, "S" },
    { 1023, "S" },
    { 1024, "S" },
    { 1025, "" },
    { 1026, "S" },
    { -1, NULL }
};

static const InsFormat th19_fmts[] = {
    { 534, "S" },
    { 539, "" },
    { 549, "SS" },
    { 569, "fffff" },
    { 570, "SSSSSSSSS" },
    { 571, "fffffffff" },
    { 619, "Sf" },
    { 620, "Sff" },
    { 621, "fS" },
    { 622, "S" },
    { 624, "S" },
    { 1027, "S" },
    { 1028, "f" },
    { 1029, "S" },
    { 1030, "S" },
    { 1031, "S" },
    { 1032, "S" },
    { 1033, "S" },
    { 1034, "" },
    { 1035, "" },
    { 1036, "" },
    { -1, NULL }
};

const char* find_format(const InsFormat* fmts, int id)
{
    int i;
    for (i = 0; fmts[i].ins_format; ++i) {
        if (fmts[i].id == id)
            return fmts[i].ins_format;
    }
    return NULL;
}

#pragma warning(push)
#pragma warning(disable:26819)

const char* GetFormat(int version,int32_t id)
{
    const char* ret = 0;
    switch (version) {
        /* NEWHU: 19 */
    case 19:
        if ((ret = find_format(th19_fmts, id))) break; /* fallthrough */
    case 185:
        if ((ret = find_format(th185_fmts, id))) break; /* fallthrough */
    case 18:
        if ((ret = find_format(th18_fmts, id))) break; /* fallthrough */
    case 17:
        if ((ret = find_format(th17_fmts, id))) break; /* fallthrough */
    case 165:
        if ((ret = find_format(th165_fmts, id))) break; /* fallthrough */
    case 16:
        if ((ret = find_format(th16_fmts, id))) break; /* fallthrough */
    case 15:
        if ((ret = find_format(th15_fmts, id))) break; /* fallthrough */
    case 143:
        if ((ret = find_format(th143_fmts, id))) break; /* fallthrough */
    case 14:
        if ((ret = find_format(th14_fmts, id))) break; /* fallthrough */
    case 13:
        if ((ret = find_format(th13_fmts, id))) break; /* fallthrough */
    case 128:
        if ((ret = find_format(th128_fmts, id))) break; /* fallthrough */
    case 125:
        if ((ret = find_format(th125_fmts, id))) break; /* fallthrough */
    case 12:
        if ((ret = find_format(th12_fmts, id))) break; /* fallthrough */
    case 11:
        if ((ret = find_format(th11_fmts, id))) break; /* fallthrough */
    case 103:
        if ((ret = find_format(alcostg_fmts, id))) break; /* fallthrough */
    case 10:
        ret = find_format(th10_fmts, id);
        break;
    default:
        return NULL;
    }
    return ret;
}

#pragma warning(pop)