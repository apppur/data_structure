#ifndef _KMP_H
#define _KMP_H

#include <iostream>
#include <string>
#include <vector>

class KMP {
    public:
        KMP() {}
        KMP(std::string content, std::string sub) 
            : m_content(content), m_sub(sub)
        {
            for (int i = 0; i < m_sub.size() + 1; i++) {
                m_next.push_back(0);
            }
        }
        ~KMP() {}

        void InitNext();
        void Next();
        int Search();

    private:
        std::string m_content;
        std::string m_sub;
        std::vector<int> m_next;
};

#endif

void KMP::InitNext() 
{
    int len = m_sub.size();
    m_next[0] = -1;
    int k = 0;
    for (int q = 0; q < len; q++) {
        m_next[q+1] = m_next[q] + 1;
        while (m_next[q+1] > 0 && m_sub[q] != m_sub[m_next[q+1]-1]) {
            m_next[q+1] = m_next[m_next[q+1]-1] + 1;
        }
    }

    for (auto v : m_next) {
        std::cout << v << '\t';
    }
    std::cout << std::endl;
}

void KMP::Next() 
{
    int len = m_sub.size();
    int k;
    m_next[0] = -1;
    for (int i = 1; i <= len; i++) {
        k = m_next[i-1];
        while (k >= 0) {
            if (m_sub[i-1] == m_sub[k])
                break;
            else
                k = m_next[k];
        }
        m_next[i] = k + 1;
    }
    for (auto v : m_next) {
        std::cout << v << '\t';
    }
    std::cout << std::endl;
}

int KMP::Search() {
    int co_len = m_content.size();
    int su_len = m_sub.size();
    int i = 0;
    int k = 0;
    while (i < co_len) {
        if (k == -1) {
            i++;
            k = 0;
        } else if (m_content[i] == m_sub[k]) {
            i++;
            k++;
            if (k == su_len)
                return 1;
        } else {
            k = m_next[k];
        }
    }

    return 0;
}
