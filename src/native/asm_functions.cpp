#include "asm_functions.h"

/**
 * ������� ��� �������� �������� � ������
 *
 * text - ������ ��� �������� ��������
 * 
 * ���������� ������������� �������� ������ ���������� 
 * �������� � ������ �� ����������� ������� ����� ������
 */
int asm_string_length(const char * text)
{
	int result;
	__asm {
			mov edi, text			// �������� ������
			mov eax, 0				// ������� ��������
		REPEAT :
			cmp byte ptr [edi], 0	// ���������� ������ �������� ������ � '\0'
			je COMPLETE				// ���� �����, ���������� ���������
			inc eax					// ����� ����������� �������
			inc edi					// �������� �� ��������� ������
			jmp REPEAT				// ���������
		COMPLETE :
			mov result, eax			// ���������� ���������
	}
	return result;

}

/**
 * ������� ��� ������ ������� ��������� ��������� � �������� ������
 * search_in - �������� ������ � ������� ����
 * substring - ���������, ������� ���� � ��������
 *
 * ���������� ����� �����, ������ ������� ������� ������� �������� ����� � �������� ������
 * -1, ���� ��������� �� ������� � �������� ������
 */ 
int asm_index_of(const char * search_in, const char * substring)
{
	int slen = asm_string_length(search_in);
	int wlen = asm_string_length(substring);
	int result;
	__asm {
			mov esi, search_in
			mov edi, substring
			mov eax, 0h				// ������ ������� ��������� ���������
			mov ecx, slen			// ������ �������� ������
		COMPARE_S :
			mov ebx, ecx			// ���������� �������� �������� �� �������� �������
			mov edx, esi			// ���������� ������� ������� � �������� ������
			mov ecx, wlen			// ����� ���������
		COMPARE_W :
			cmpsb
			je FOUND
			jne NOTFOUND
		FOUND :
			loop COMPARE_W
			jmp COMPARE_RESULT
		NOTFOUND :
			mov esi, edx			// ������������ ������� � �������� ������
			inc esi					// ������� � ���������� ������� � �������� ������
			mov edi, substring		// ���������� edi �� ������ ���������
			mov ecx, ebx			// �������������� �������� �������� � �������� �������
			inc eax					// ����������� ������� ������� � �������� ������
			loop COMPARE_S
			mov eax, -1				// -1 ���� ��������� �� ������� �������� ������
		COMPARE_RESULT:
			mov result, eax
	}
	return result;
}

/**
 * ������� ��������� ��������� �� ������
 * 
 * text - �������� �����
 * begin - ������ ������ ���������
 * length -������ ���������
 *
 * ���������� ����� ������, ���������� ���������� �������� ������
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
 * ������� ��������� �����
 *	
 * first, second - ������������ ������
 *
 * ���������� ����� �����: 1 - ���� ������ �����, 0 - ���� ������ �� �����
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
