#pragma once
#include "CUrlParsingError.h"

enum class Protocol
{
	HTTP,
	HTTPS
};

std::ostream& operator<<(std::ostream& out, Protocol protocol);

class CHttpUrl
{
public:
    // выполн€ет парсинг строкового представлени€ URL-а, в случае ошибки парсинга
    // выбрасывает исключение CUrlParsingError, содержащее текстовое описание ошибки
    CHttpUrl(std::string const& url);

    /* инициализирует URL на основе переданных параметров.
        ѕри недопустимости входных параметров выбрасывает исключение
        std::invalid_argument
        ≈сли им€ документа не начинаетс€ с символа /, то добавл€ет / к имени документа
    */
    CHttpUrl(
        std::string const& domain,
        std::string const& document,
        Protocol protocol = Protocol::HTTP);

    /* инициализирует URL на основе переданных параметров.
        ѕри недопустимости входных параметров выбрасывает исключение
        std::invalid_argument
        ≈сли им€ документа не начинаетс€ с символа /, то добавл€ет / к имени документа
    */
    CHttpUrl(
        std::string const& domain,
        std::string const& document,
        Protocol protocol,
        unsigned short port);

    // возвращает строковое представление URL-а. ѕорт, €вл€ющийс€ стандартным дл€
    // выбранного протокола (80 дл€ http и 443 дл€ https) в эту строку
    // не должен включатьс€
    std::string GetURL()const;

    // возвращает доменное им€
    std::string GetDomain()const;

    /*
        ¬озвращает им€ документа. ѕримеры:
            /
            /index.html
            /images/photo.jpg
    */
    std::string GetDocument()const;

    // возвращает тип протокола
    Protocol GetProtocol()const;

    // возвращает номер порта
    unsigned short GetPort()const;
private:
	Protocol m_protocol;
	std::string m_domain;
	std::string m_document;
	unsigned short m_port;
    bool IsDomainValid(const std::string& domain);
    bool IsDocumentValid(const std::string& document);
    Protocol GetProtocolByString(const std::string& str);
    unsigned short ParsePort(const std::string& portStr);
    static std::string StrToLowerCase(const std::string& str);
};

