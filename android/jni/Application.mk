APP_STL := gnustl_static
APP_CPPFLAGS := -frtti -DCOCOS2D_DEBUG=1 -std=c++11 -Wno-literal-suffix -fsigned-char   
LOCAL_CFLAGS += -Wno-format-y2k -fpermissive
APP_CFLAGS += -Wno-error=format-security 
