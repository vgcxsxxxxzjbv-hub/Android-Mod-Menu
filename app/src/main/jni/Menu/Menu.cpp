#include "Includes/obfuscate.h"
#include "Menu/Menu.hpp"

bool iconValid = false;
bool settingsValid = false;
bool featuresValid = false;
bool initValid = false;

//Big letter cause crash
void setText(JNIEnv *env, jobject obj, const char* text){
    jclass html = (*env).FindClass(OBFUSCATE("android/text/Html"));
    jmethodID fromHtml = (*env).GetStaticMethodID(html, OBFUSCATE("fromHtml"), OBFUSCATE("(Ljava/lang/String;)Landroid/text/Spanned;"));

    jclass textView = (*env).FindClass(OBFUSCATE("android/widget/TextView"));
    jmethodID setText = (*env).GetMethodID(textView, OBFUSCATE("setText"), OBFUSCATE("(Ljava/lang/CharSequence;)V"));

    jstring jstr = (*env).NewStringUTF(text);
    (*env).CallVoidMethod(obj, setText,  (*env).CallStaticObjectMethod(html, fromHtml, jstr));
}

jstring Icon(JNIEnv *env, jobject thiz) {
    // Humne yahan se lamba Base64 hata diya hai kyunki hum WebView use karenge
    return nullptr; 
}

jstring IconWebViewData(JNIEnv *env, jobject thiz) {
    // Yahan humne HTML aur CSS ke through Red Banner banaya hai
    const char* redBannerHTML = R"(
        <html>
        <head>
            <style>
                body {
                    margin: 0;
                    padding: 0;
                    display: flex;
                    justify-content: center;
                    align-items: center;
                    height: 100vh;
                    background-color: transparent;
                }
                .banner {
                    background-color: #D50000; /* Dark Red */
                    color: white;
                    padding: 10px 20px;
                    border-radius: 30px;
                    font-family: Arial, sans-serif;
                    font-weight: bold;
                    font-size: 14px;
                    display: flex;
                    align-items: center;
                    box-shadow: 0 4px 6px rgba(0,0,0,0.3);
                    white-space: nowrap;
                }
                .icon {
                    margin-right: 10px;
                    font-size: 10px;
                }
                .close {
                    margin-left: 15px;
                    font-size: 16px;
                    cursor: pointer;
                }
            </style>
        </head>
        <body>
            <div class="banner" onclick="window.location.href='modmenu://toggle'">
                <span class="icon">▶</span>
                PAINEL GRINGO XP
                <span class="close" onclick="window.location.href='modmenu://close'">✕</span>
            </div>
        </body>
        </html>
    )";
    
    // Base64 mein convert karke return kar rahe hain taaki WebView easily load kar le
    return env->NewStringUTF(redBannerHTML);
}

jobjectArray SettingsList(JNIEnv *env, jobject activityObject) {
    jobjectArray ret;

    const char *features[] = {
            OBFUSCATE("Category_Settings"),
            OBFUSCATE("-1_Toggle_Save feature preferences"), 
            OBFUSCATE("Category_Menu"),
            OBFUSCATE("-6_Button_<font color='red'>Close settings</font>"),
    };

    int Total_Feature = (sizeof features / sizeof features[0]); 
    ret = (jobjectArray)
            env->NewObjectArray(Total_Feature, env->FindClass(OBFUSCATE("java/lang/String")),
                                env->NewStringUTF(""));
    int i;
    for (i = 0; i < Total_Feature; i++)
        env->SetObjectArrayElement(ret, i, env->NewStringUTF(features[i]));

    return (ret);
}
