#include "HelloJni.h"
#include <stdio.h>
#include <string.h>

JNIEXPORT jstring JNICALL Java_HelloJni_getStringFromCStatic(JNIEnv * env, jclass clz){
    return (*env)->NewStringUTF(env, "C String static");
}

JNIEXPORT jstring JNICALL Java_HelloJni_getStringFromCNonStatic(JNIEnv * env, jobject obj){
    return (*env)->NewStringUTF(env, "C string non static");
}

JNIEXPORT jstring JNICALL Java_HelloJni_accessField(JNIEnv * env, jobject obj){
    jclass jclz = (*env)->GetObjectClass(env, obj);
    jfieldID fid = (*env)->GetFieldID(env, jclz, "key", "Ljava/lang/String;");
    jstring jstr = (*env)->GetObjectField(env, obj, fid);
    char* c_str = (*env)->GetStringUTFChars(env, jstr, NULL);
    char text[30] = "solarex";
    strcat(text, c_str);
    jstring new_str = (*env)->NewStringUTF(env, text);
    (*env)->SetObjectField(env, obj, fid, new_str);
    (*env)->ReleaseStringChars(env, new_str, c_str);
    return new_str;
}

JNIEXPORT void JNICALL Java_HelloJni_accessStaticField(JNIEnv * env, jobject obj){
    jclass jclz = (*env)->GetObjectClass(env, obj);
    jfieldID fid = (*env)->GetStaticFieldID(env, jclz, "count", "I");
    jint count = (*env)->GetStaticIntField(env, jclz, fid);
    count++;
    (*env)->SetStaticIntField(env, jclz, fid, count);
}

JNIEXPORT void JNICALL Java_HelloJni_accessMethod(JNIEnv * env, jobject obj){
    jclass jclz = (*env)->GetObjectClass(env, obj);
    jmethodID mid = (*env)->GetMethodID(env, jclz, "getRandomInt", "(I)I");
    jint random = (*env)->CallIntMethod(env, obj, mid, 200);
    printf("C random = %d\n", random);
}

JNIEXPORT void JNICALL Java_HelloJni_accessStaticMethod(JNIEnv * env, jobject obj){
    jclass jclz = (*env)->GetObjectClass(env, obj);
    jmethodID mid = (*env)->GetStaticMethodID(env, jclz, "getUUID","()Ljava/lang/String;");
    jstring uuid = (*env)->CallStaticObjectMethod(env, jclz, mid);
    char * uuid_c = (*env)->GetStringUTFChars(env, uuid, NULL);
    printf("uuid_c : %s\n", uuid_c);
    char filename[100];
    sprintf(filename, "%s.txt", uuid_c);
    printf("filename : %s\n", filename);

    FILE *fp = fopen(filename, "w");
    fputs("Solarex", fp);
    fclose(fp);
    printf("write file success\n");
}

JNIEXPORT jobject JNICALL Java_HelloJni_accessConstructor(JNIEnv * env, jobject obj){
    jclass jclz = (*env)->FindClass(env, "java/util/Date");
    jmethodID mid = (*env)->GetMethodID(env, jclz, "<init>", "()V");
    jobject date_obj = (*env)->NewObject(env, jclz, mid);
    jmethodID gettime_mid = (*env)->GetMethodID(env, jclz, "getTime", "()J");
    jlong time = (*env)->CallLongMethod(env, date_obj, gettime_mid);
    printf("c time: %lld\n", time);
    return date_obj;
}

JNIEXPORT jstring JNICALL Java_HelloJni_accessUTFChars(JNIEnv * env, jobject obj, jstring str){
    char * c_str = (*env)->GetStringUTFChars(env, str, NULL);
    printf("c_str: %s\n", c_str);
    (*env)->ReleaseStringChars(env, str, c_str);
    c_str = "北上广深杭";
    jclass str_clz = (*env)->FindClass(env, "java/lang/String");
    jmethodID jmid = (*env)->GetMethodID(env, str_clz, "<init>", "([BLjava/lang/String;)V");
    //jstring -> jbyte array
    jbyteArray bytes = (*env)->NewByteArray(env, strlen(c_str));
    (*env)->SetByteArrayRegion(env, bytes, 0, strlen(c_str), c_str);
    jstring charset = (*env)->NewStringUTF(env, "UTF-8");
    return (*env)->NewObject(env, str_clz, jmid, bytes, charset);
}

JNIEXPORT void JNICALL Java_HelloJni_sortArray(JNIEnv * env, jobject obj, jintArray arr){
    int compare(jint *a, jint *b);
    jint *elements = (*env)->GetIntArrayElements(env, arr, NULL);
    if ( elements == NULL){
        return;
    }
    int len = (*env)->GetArrayLength(env, arr);
    qsort(elements, len, sizeof(jint), compare);
    (*env)->ReleaseIntArrayElements(env, arr, elements, JNI_COMMIT);
}

int compare(jint *a, jint *b){
    return *a - *b;
}

JNIEXPORT jobjectArray JNICALL Java_HelloJni_getStringArray(JNIEnv *env, jobject obj, jint size) {
    jobjectArray result;
    jclass str_clz;
    int i;
    str_clz = (*env)->FindClass(env, "java/lang/String");
    if(str_clz == NULL){
        return NULL;
    }
    result = (*env)->NewObjectArray(env, size, str_clz, obj);
    
    for(i = 0; i < size; i++){
        char *c_char = (char*)malloc(sizeof(char)*50);
        memset(c_char,0, 50);
        sprintf(c_char, "Solarex %d", i);
        jstring str = (*env)->NewStringUTF(env, c_char);
        (*env)->SetObjectArrayElement(env, result, i, str);
        free(c_char);
        c_char = NULL;
    }
    return result;
}

























