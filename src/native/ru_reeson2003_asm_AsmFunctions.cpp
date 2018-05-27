#include "ru_reeson2003_asm_AsmFunctions.h"
#include "asm_functions.h"

JNIEXPORT jint JNICALL Java_ru_reeson2003_asm_AsmFunctions_asm_1string_1length(JNIEnv * jniEnv, jobject obj, jstring text)
{
	const char * a_text = jniEnv->GetStringUTFChars(text, 0);
	return asm_string_length(a_text);
}

JNIEXPORT jint JNICALL Java_ru_reeson2003_asm_AsmFunctions_asm_1index_1of(JNIEnv * jniEnv, jobject obj, jstring search_in, jstring substring)
{
	const char * a_search_in = jniEnv->GetStringUTFChars(search_in, 0);
	const char * a_substring = jniEnv->GetStringUTFChars(substring, 0);
	return asm_index_of(a_search_in, a_substring);
}

JNIEXPORT jstring JNICALL Java_ru_reeson2003_asm_AsmFunctions_asm_1substring(JNIEnv *jniEnv, jobject obj, jstring text, jint begin, jint length)
{
	const char * a_text = jniEnv->GetStringUTFChars(text, 0);
	const char * a_substring = asm_subctring(a_text, begin, length);
	jstring result = jniEnv->NewStringUTF(a_substring);
	return result;
}

