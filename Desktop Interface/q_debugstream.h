//As per forum:
//http://www.qtforum.org/article/39768/redirecting-std-cout-std-cerf-qdebug-to-qtextedit.html
//A couple of lines added to ensure newlines go between each call.
//Thanks, James!

#ifndef Q_DEBUGSTREAM_H
#define Q_DEBUGSTREAM_H

#include <iostream>
#include <streambuf>
#include <string>

#include "QTextEdit.h"

class Q_DebugStream : public std::basic_streambuf<char>
{
public:
    Q_DebugStream(std::ostream &stream, QTextEdit* text_edit) : m_stream(stream)
    {
        log_window = text_edit;
        m_old_buf = stream.rdbuf();
        stream.rdbuf(this);
    }

    ~Q_DebugStream()
    {
        m_stream.rdbuf(m_old_buf);
    }

    static void registerQDebugMessageHandler(){
        qInstallMessageHandler(myQDebugMessageHandler);
    }

private:

    static void myQDebugMessageHandler(QtMsgType, const QMessageLogContext &, const QString &msg)
    {
        std::cout << msg.toStdString().c_str();
    }

protected:

    //This is called when a std::endl has been inserted into the stream
    virtual int_type overflow(int_type v)
    {
        if (v == '\n')
        {
            log_window->append("");
        }
        return v;
    }


    virtual std::streamsize xsputn(const char *p, std::streamsize n)
    {
        QString str(p);
        if(str.contains("\n")){
            QStringList strSplitted = str.split("\n");

            log_window->moveCursor (QTextCursor::End);
            log_window->insertPlainText (strSplitted.at(0)); //Index 0 is still on the same old line

            for(int i = 1; i < strSplitted.size(); i++){
                log_window->append(strSplitted.at(i));
                log_window->append("\n");
            }
        }else{
            log_window->moveCursor (QTextCursor::End);
            log_window->insertPlainText (str);
            log_window->insertPlainText ("\n");
        }
        return n;
    }

private:
    std::ostream &m_stream;
    std::streambuf *m_old_buf;
    QTextEdit* log_window;
};


#endif // Q_DEBUGSTREAM_H
