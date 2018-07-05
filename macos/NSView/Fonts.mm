#include "CocoUtil.h"

using namespace Upp;

#if 0
void ListFonts()
{
	AutoreleasePool __;

    CFRef<CTFontCollectionRef> collection = CTFontCollectionCreateFromAvailableFonts(0);
    if (!collection) return;
    CFRef<CFArrayRef> fonts = CTFontCollectionCreateMatchingFontDescriptors(collection);
    if(!fonts) return;
	int count = CFArrayGetCount(fonts);
    for(int i = 0; i < count; ++i) {
		CTFontDescriptorRef font = (CTFontDescriptorRef)CFArrayGetValueAtIndex(fonts, i);
		DLOG("---------");
		CFRef<CFStringRef> family_name = (CFStringRef)CTFontDescriptorCopyAttribute(font, kCTFontFamilyNameAttribute);
        DDUMP(ToString(family_name));
		CFRef<CFStringRef> font_name = (CFStringRef)CTFontDescriptorCopyAttribute(font, kCTFontNameAttribute);
        DDUMP(ToString(font_name));
        CFRef<CFDictionaryRef> styles = (CFDictionaryRef)CTFontDescriptorCopyAttribute(font, kCTFontTraitsAttribute);
		if(styles) {
			CFNumberRef weight = (CFNumberRef)CFDictionaryGetValue(styles, kCTFontWeightTrait);
            if(weight) {
                ASSERT(CFNumberIsFloatType(weight));
                double d;
                if(CFNumberGetValue(weight, kCFNumberDoubleType, &d)) {
                    DDUMP(d);
//                    if (d > 0.0)
//                        fontWeight = QFont::Bold;
                }
            }
            CFNumberRef italic = (CFNumberRef)CFDictionaryGetValue(styles, kCTFontSlantTrait);
            if(italic) {
                ASSERT(CFNumberIsFloatType(italic));
                double d;
                if (CFNumberGetValue(italic, kCFNumberDoubleType, &d)) {
                    DDUMP(d);
//                    if (d > 0.0)
//                        fontStyle = QFont::StyleItalic;
                }
            }
        }
    }
}
#endif