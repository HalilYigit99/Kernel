#pragma once

#include "Nano.hpp"
#include "Object.hpp"
#include "Array.hpp"

namespace nano
{

    typedef class String string;
    
    class Object;

    class String {

        private:
            cstring x;

        public:

            static String Empty;

            static int Compare(string strA, string strB);

            static int Compare(string strA, string strB, bool ignoreCase);

            String();

            String (byte x);
            String (str x);
            String (cstring x);

            String(String* x);
            
            ~String();

            dword Length();

            Object Clone();

            int CompareTo(Object value);

            int CompareTo(string strB);

            bool Contains(string value);

            bool EndsWith(string value);

            bool Equals(Object obj);

            bool Equals(string value);

            int IndexOf(byte value);

            int IndexOf(byte value, int startIndex);

            int IndexOf(byte value, int startIndex, int count);

            int IndexOf(string value);

            int IndexOf(string value, int startIndex);

            int IndexOf(string value, int startIndex, int count);

            string Insert(int startIndex, string value);

            int LastIndexOf(byte value);

            int LastIndexOf(string value);

            string Remove(int startIndex);

            string Remove(int startIndex, int count);

            string Replace(char oldChar, char newChar);

            string Replace(string oldValue, string newValue);

            Array<String> Split(Array<byte> seperator);

            bool StartsWith(string value);
            
            string Substring(int startIndex);

            string Substring(int startIndex, int length);

            Array<byte> ToCharArray();

            string ToLower();

            String ToString() { return *this; }

            string ToUpper();

            string Trim();

            string Trim(Array<byte> trimChars);

            string TrimEnd();

            string TrimEnd(Array<byte> trimChars);

            string TrimStart();

            string TrimStart(Array<byte> trimChars);

            cstring CStr() const { return this->x; }

            void operator = (String& x);

            bool Contains(Array<byte> trimChars, byte character);

            String operator + (String str);

            bool operator == (String str);

            byte operator [](dword index);

            void operator += (byte data);

            void operator += (Array<byte> dataS);

    };
    
} // namespace nano

