#include "String.hpp"
#include "Array.hpp"

#include <string.h>
#include <stdlib.h>

namespace nano
{

    String String::Empty = "";

    byte tolower(byte c)
    {
        if (c >= 'A' && c <= 'Z')
        {
            return c - 'A' + 'a';
        }
        return c;
    }

    byte toupper(byte c)
    {
        if (c >= 'a' && c <= 'z')
        {
            return c - 'a' + 'A';
        }
        return c;
    }

    String::String()
    {
        this->x = (cstring)0;
    }

    String::String(byte x)
    {
        byte *_x = new byte[2];
        _x[0] = x;
        _x[1] = 0;
        this->x = (cstring)_x;
    }

    String::String(str x)
    {
        this->x = (cstring)x;
    }

    String::String(cstring x)
    {
        this->x = x;
    }

    String::String(String *x)
    {
        this->x = x->x;
    }

    String::~String()
    {
        if ((word)this->x >= (word)__malloc_heap_start)
            delete this->x;
    }

    dword String::Length()
    {
        return strlen(this->x);
    }

    object String::Clone()
    {
        String *other = new String(this);
        return object(*other);
    }

    int String::Compare(string strA, string strB)
    {
        return strcmp(strA.x, strB.x);
    }

    int String::Compare(string strA, string strB, bool ignoreCase)
    {
        return strcmp(strA.x, strB.x);
    }

    int String::CompareTo(object value)
    {
        cstring str = value;
        return strcmp(this->x, str);
    }

    int String::CompareTo(string strB)
    {
        return strcmp(this->x, strB.x);
    }

    bool String::Contains(string value)
    {
        cstring str = this->x;
        cstring find = value.x;

        cstring findBuffer;
        cstring searchBuffer;

        while (*str)
        {
            if (*str == *find)
            {
                bool sucsess = true;
                findBuffer = find;
                searchBuffer = str;
                while (*searchBuffer)
                {
                    if (*findBuffer != *searchBuffer)
                    {
                        sucsess = false;
                        break;
                    }
                    searchBuffer++;
                    findBuffer++;
                }
                if (sucsess)
                    return true;
            }
            str++;
        }

        return false;
    }

    bool String::EndsWith(string value)
    {
        cstring buffer = this->x;
        cstring search = value.x;
        int32_t searchLen = strlen(search);
        int32_t bufferLen = strlen(buffer);

        if (bufferLen >= searchLen)
        {
            buffer += (bufferLen - searchLen);
            return strcmp(buffer, search) == 0;
        }

        return false;
    }

    bool String::Equals(object obj)
    {
        cstring str = obj;
        return strcmp(str, this->x) == 0;
    }

    bool String::Equals(string value)
    {
        cstring str = value.x;
        return strcmp(str, this->x) == 0;
    }

    int String::IndexOf(byte value)
    {
        return this->IndexOf(value, 0);
    }

    int String::IndexOf(byte value, int startIndex)
    {
        return this->IndexOf(value, startIndex, -1);
    }

    int String::IndexOf(byte value, int startIndex, int count)
    {

        if (count < 0)
        {
            count = this->Length();
        }
        else if (count == 0)
            return -1;

        int index = startIndex;
        cstring buffer = this->x;
        buffer += startIndex;

        while (*buffer)
        {

            if (*buffer == value)
                return index;

            count--;
            if (count == 0)
                return -1;

            buffer++;
            index++;
        }

        return -1;
    }

    int String::IndexOf(string value)
    {
        return this->IndexOf(value, 0);
    }

    int String::IndexOf(string value, int startIndex)
    {
        return this->IndexOf(value, startIndex, -1);
    }

    int String::IndexOf(string value, int startIndex, int count)
    {
        if (count < 0)
        {
            count = this->Length();
        }

        int index = startIndex;
        cstring buffer = this->x;
        cstring findBuffer = value.x;
        buffer += index;

        while (*buffer)
        {

            if (*buffer == *findBuffer)
            {
                int result = strcmp(buffer, findBuffer);
                if (result == 0)
                    return index;
            }

            index++;
            buffer++;
        }

        return -1;
    }

    string String::Insert(int startIndex, string value)
    {
        int valueLen = value.Length();
        int selfLen = this->Length();
        int bufferLen = valueLen + selfLen;

        str buffer = (str) new byte[bufferLen + 1];

        buffer[bufferLen] = 0;

        for (int index = 0; index < startIndex - 1; index++)
        {
            buffer[index] = this->x[index];
        }

        for (int index = startIndex; index < (valueLen - 1); index++)
        {
            buffer[index] = this->x[index];
        }

        for (int index = startIndex + valueLen; index < bufferLen; index++)
        {
            buffer[index] = this->x[index];
        }

        String *string1 = new String(buffer);

        return *string1;
    }

    int String::LastIndexOf(byte value)
    {
        cstring buffer = this->x;
        int32_t selfSize = this->Length();

        for (int index = selfSize - 1; index >= 0; index--)
        {
            if (buffer[index] == value)
                return index;
        }

        return -1;
    }

    int String::LastIndexOf(string value)
    {
        cstring bufferSelf = this->x;
        int32_t selfSize = this->Length();
        int32_t valueSize = value.Length();
        cstring otherBuffer = value.x;

        for (int index = selfSize - 1 - valueSize; index >= 0; index--)
        {
            if (bufferSelf[index] == *otherBuffer)
            {
                if (strcmp(bufferSelf + index, otherBuffer) == 0)
                {
                    return index;
                }
            }
        }

        return -1;
    }

    string String::Remove(int startIndex)
    {
        if (startIndex <= 0)
            return String::Empty;

        str newBuffer = (str) new byte[startIndex + 1];
        newBuffer[startIndex] = 0;

        for (int i = 0; i < startIndex; i++)
        {
            newBuffer[i] = this->x[i];
        }

        String *_Ret = new String(newBuffer);

        return *_Ret;
    }

    string String::Remove(int startIndex, int count)
    {
        if (startIndex <= 0)
            return String::Empty;
        if (count <= 0)
            return *this;

        int length = this->Length();
        int newBufferLength = length - count;

        str newBuffer = (str) new byte[newBufferLength + 1];
        newBuffer[newBufferLength] = 0;

        for (int i = 0; i < startIndex; i++)
        {
            newBuffer[i] = this->x[i];
        }

        if (newBufferLength > startIndex)
        {

            for (int i = startIndex + count; i < length; i++)
            {
                newBuffer[i] = this->x[i];
            }
        }

        String *_Ret = new String(newBuffer);

        return *_Ret;
    }

    string String::Replace(char oldChar, char newChar)
    {
        int length = this->Length();
        char *newBuffer = new char[length + 1];
        for (int i = 0; i < length; i++)
        {
            newBuffer[i] = (this->x[i] == oldChar) ? newChar : this->x[i];
        }
        newBuffer[length] = '\0';
        String *result = new String(newBuffer);
        return *result;
    }

    string String::Replace(string oldValue, string newValue)
    {
        int index = this->IndexOf(oldValue);
        if (index == -1)
            return *this;

        int length = this->Length();
        int newBufferLength = length - oldValue.Length() + newValue.Length();

        str newBuffer = (str) new byte[newBufferLength + 1];
        newBuffer[newBufferLength] = 0;

        for (int i = 0; i < index; i++)
        {
            newBuffer[i] = this->x[i];
        }

        for (int i = 0; i < (int)newValue.Length(); i++)
        {
            newBuffer[index + i] = newValue.x[i];
        }

        if (newBufferLength > (int)(index + oldValue.Length()))
        {

            for (int i = index + oldValue.Length(); i < length; i++)
            {
                newBuffer[i + newValue.Length() - oldValue.Length()] = this->x[i];
            }
        }

        String *_Ret = new String(newBuffer);

        return *_Ret;
    }

    Array<String> String::Split(Array<byte> separator)
    {
        Array<String> result;
        dword startIndex = 0;
        int index = this->IndexOf(separator[0]);

        while (index != -1)
        {
            result.Add(this->Substring(startIndex, index - startIndex));
            startIndex = index + separator.Count();
            index = this->IndexOf(separator[0], startIndex);
        }

        if (startIndex < this->Length())
        {
            result.Add(this->Substring(startIndex));
        }

        return result;
    }

    bool String::StartsWith(string value)
    {
        cstring buffer = this->x;
        cstring search = value.x;
        int32_t searchLen = strlen(search);
        int32_t bufferLen = strlen(buffer);

        if (bufferLen >= searchLen)
        {
            return strncmp(buffer, search, searchLen) == 0;
        }

        return false;
    }

    string String::Substring(int startIndex)
    {
        return this->Substring(startIndex, this->Length() - startIndex);
    }

    string String::Substring(int startIndex, int length)
    {
        if (startIndex < 0 || length < 0 || (startIndex + length) > (int)this->Length())
            return String::Empty;

        str newBuffer = (str) new byte[length + 1];
        newBuffer[length] = 0;

        for (int i = 0; i < length; i++)
        {
            newBuffer[i] = this->x[startIndex + i];
        }

        String *_Ret = new String(newBuffer);

        return *_Ret;
    }

    Array<byte> String::ToCharArray()
    {
        Array<byte> result;
        int length = this->Length();

        for (int i = 0; i < length; i++)
        {
            result.Add(this->x[i]);
        }

        return result;
    }

    string String::ToLower()
    {
        int length = this->Length();
        char *newBuffer = new char[length + 1];
        for (int i = 0; i < length; i++)
        {
            newBuffer[i] = tolower(this->x[i]);
        }
        newBuffer[length] = '\0';
        String *result = new String(newBuffer);
        return *result;
    }

    string String::ToUpper()
    {
        int length = this->Length();
        char *newBuffer = new char[length + 1];
        for (int i = 0; i < length; i++)
        {
            newBuffer[i] = toupper(this->x[i]);
        }
        newBuffer[length] = '\0';
        String *result = new String(newBuffer);
        return *result;
    }

    string String::Trim()
    {
        return this->Trim(Array<byte>(new byte[1]{' '}));
    }

    string String::Trim(Array<byte> trimChars)
    {
        int startIndex = 0;
        int endIndex = this->Length() - 1;

        while (startIndex < (int)this->Length() && this->Contains(trimChars, this->x[startIndex]))
        {
            startIndex++;
        }

        while (endIndex >= 0 && this->Contains(trimChars, this->x[endIndex]))
        {
            endIndex--;
        }

        if (startIndex > endIndex)
            return String::Empty;

        return this->Substring(startIndex, endIndex - startIndex + 1);
    }

    string String::TrimEnd()
    {
        return this->TrimEnd(Array<byte>(new byte[1]{' '}));
    }

    string String::TrimEnd(Array<byte> trimChars)
    {
        int endIndex = this->Length() - 1;

        while (endIndex >= 0 && this->Contains(trimChars, this->x[endIndex]))
        {
            endIndex--;
        }

        if (endIndex < 0)
            return String::Empty;

        return this->Substring(0, endIndex + 1);
    }

    string String::TrimStart()
    {
        return this->TrimStart(Array<byte>(new byte[1]{' '}));
    }

    string String::TrimStart(Array<byte> trimChars)
    {
        int startIndex = 0;

        while (startIndex < (int)this->Length() && this->Contains(trimChars, this->x[startIndex]))
        {
            startIndex++;
        }

        if (startIndex > 0)
        {
            return this->Substring(startIndex);
        }

        return *this;
    }

    void String::operator=(String &x)
    {
        this->x = x.x;
    }

    bool String::Contains(Array<byte> trimChars, byte character)
    {
        for (int i = 0; i < (int32_t)trimChars.Count(); i++)
        {
            if (trimChars[i] == character)
                return true;
        }
        return false;
    }

    String String::operator+(String str1)
    {
        int length1 = this->Length();
        int length2 = str1.Length();
        int newBufferLength = length1 + length2;

        str newBuffer = (str) new byte[newBufferLength + 1];
        newBuffer[newBufferLength] = 0;

        for (int i = 0; i < length1; i++)
        {
            newBuffer[i] = this->x[i];
        }

        for (int i = 0; i < length2; i++)
        {
            newBuffer[length1 + i] = str1.x[i];
        }

        String *result = new String(newBuffer);

        return *result;
    }

    bool String::operator==(String str)
    {
        return this->Equals(str);
    }

    byte String::operator[](dword index)
    {
        if (index < 0 || index >= (dword)this->Length())
            return 0;

        return this->x[index];
    }

    void String::operator+=(byte data)
    {
        int length = this->Length();
        str newBuffer = (str) new byte[length + 2];
        newBuffer[length + 1] = 0;

        for (int i = 0; i < length; i++)
        {
            newBuffer[i] = this->x[i];
        }

        newBuffer[length] = data;

        this->x = newBuffer;
    }

    void String::operator+=(Array<byte> dataS)
    {
        int length = this->Length();
        int dataLength = dataS.Count();
        int newBufferLength = length + dataLength;

        str newBuffer = (str) new byte[newBufferLength + 1];
        newBuffer[newBufferLength] = 0;

        for (int i = 0; i < length; i++)
        {
            newBuffer[i] = this->x[i];
        }

        for (int i = 0; i < dataLength; i++)
        {
            newBuffer[length + i] = dataS[i];
        }

        this->x = newBuffer;
    }

} // namespace nano
