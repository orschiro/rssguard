#include <QString>
#include <QStringList>
#include <QDateTime>
#include <QLocale>
#include <QRegExp>

#include "core/defs.h"
#include "core/textfactory.h"


TextFactory::TextFactory() {
}

TextFactory::~TextFactory() {
}

QDateTime TextFactory::parseDateTime(const QString &date_time) {
  QString date = date_time.simplified();
  QDateTime dt;
  QString temp;
  QLocale locale(QLocale::C);
  QStringList date_patterns;
  date_patterns << "yyyy-MM-ddTHH:mm:ss" << "MMM dd yyyy hh:mm:ss" <<
                   "MMM hd yyyy hh:mm:ss" << "ddd, dd MMM yyyy HH:mm:ss" <<
                   "dd MMM yyyy" << "yyyy-MM-dd HH:mm:ss.z" << "yyyy-MM-dd" <<
                   "YYYY" << "YYYY-MM" << "YYYY-MM-DD" << "YYYY-MM-DDThh:mmTZD" <<
                   "YYYY-MM-DDThh:mm:ssTZD";

  // Iterate over patterns and check if input date/time matches the pattern.
  foreach (QString pattern, date_patterns) {
    temp = date.left(pattern.size());
    dt = locale.toDateTime(temp, pattern);
    if (dt.isValid()) {
      return dt;
    }
  }

  qWarning("Problem with parsing date '%s', returning invalid QDateTime instance.",
           qPrintable(date));
  return QDateTime();
}

QString TextFactory::shorten(const QString &input, int text_length_limit) {
  if (input.size() > text_length_limit) {
    return input.left(text_length_limit - 3) + QString(3, '.');
  }
  else {
    return input;
  }
}