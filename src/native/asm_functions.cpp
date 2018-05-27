#include "asm_functions.h"

/**
 * Функция для подсчета символов в строке
 *
 * text - строка для подсчета символов
 * 
 * возвращает целочисленное значение равное количеству 
 * символов в строке за исключением символа конца строки
 */
int asm_string_length(const char * text)
{
	int result;
	__asm {
			mov edi, text			// исходная строка
			mov eax, 0				// счетчик итераций
		REPEAT :
			cmp byte ptr [edi], 0	// сравниваем символ исходной строки с '\0'
			je COMPLETE				// если равны, возвращаем результат
			inc eax					// иначе увеличиваем счетчик
			inc edi					// сдвигаем на следующий символ
			jmp REPEAT				// повторяем
		COMPLETE :
			mov result, eax			// возвращаем результат
	}
	return result;

}

/**
 * функция для поиска первого вхождения подстроки в исходной строке
 * search_in - исходная строка в которой ищем
 * substring - подстрока, которую ищем в исходной
 *
 * возвращает целое число, равное индексу первого символа искомого слова в исходной строке
 * -1, если подстрока не найдена в исходной сторке
 */ 
int asm_index_of(const char * search_in, const char * substring)
{
	int slen = asm_string_length(search_in);
	int wlen = asm_string_length(substring);
	int result;
	__asm {
			mov esi, search_in
			mov edi, substring
			mov eax, 0h				// индекс первого вхождения подстроки
			mov ecx, slen			// длинна исходной сторки
		COMPARE_S :
			mov ebx, ecx			// сохранение счетчика итераций по исходной стороке
			mov edx, esi			// сохранение текущей позиции в исходной строке
			mov ecx, wlen			// длина подстроки
		COMPARE_W :
			cmpsb
			je FOUND
			jne NOTFOUND
		FOUND :
			loop COMPARE_W
			jmp COMPARE_RESULT
		NOTFOUND :
			mov esi, edx			// восстановить позицию в исходной строке
			inc esi					// переход к следующему символу в исходной сторке
			mov edi, substring		// установить edi на начало подстроки
			mov ecx, ebx			// восстановление счетчика символов в исходной стороке
			inc eax					// увеличиваем счетчик позиции в исходной строке
			loop COMPARE_S
			mov eax, -1				// -1 если подстрока не найдена исходной строке
		COMPARE_RESULT:
			mov result, eax
	}
	return result;
}

/**
 * Функция получения подстроки от строки
 * 
 * text - исходный текст
 * begin - индекс начала подстроки
 * length -длинна подстроки
 *
 * возвращает новую строку, являющуюся подстрокой исходной строки
 */
char * asm_subctring(const char * text, int begin, int length)
{
	int len = length;
	char * result = new char[length + 1];
	__asm {
			mov esi, text
			mov edi, result
			add esi, begin
			mov ecx, len
		REPEAT :
			mov al, [esi]
			mov [edi], al
			inc esi
			inc edi
			cmp byte ptr [esi], 0
			je COMPLETE
			loop REPEAT
		COMPLETE :
			mov [edi], 0
	}
	return result;
}

/**
 * Функция сравнения строк
 *	
 * first, second - сравниваемые строки
 *
 * возвращает целое число: 1 - если строки равны, 0 - если строки не равны
 */
int asm_string_compare(const char * first, const char * second)
{
	int flen = asm_string_length(first);
	int slen = asm_string_length(second);
	int result;
	__asm {
			mov eax, flen
			mov ebx, slen
			cmp eax, ebx
			jne NOT_EQUAL
			mov esi, first
			mov edi, second
			mov ecx, flen
		COMPARE :
			cmpsb
			jne NOT_EQUAL
			inc esi
			inc edi
			loop COMPARE
			mov result, 1
			jmp COMPLETE
		NOT_EQUAL :
			mov result, 0
		COMPLETE :
	}
	return result;
}
