/****************************************************************************
**
**  FougTools
**  Copyright FougSys (1 Mar. 2011)
**  contact@fougsys.fr
**
** This software is a computer program whose purpose is to provide utility
** tools for the C++ language and the Qt toolkit.
**
** This software is governed by the CeCILL-C license under French law and
** abiding by the rules of distribution of free software.  You can  use,
** modify and/ or redistribute the software under the terms of the CeCILL-C
** license as circulated by CEA, CNRS and INRIA at the following URL
** "http://www.cecill.info".
**
** As a counterpart to the access to the source code and  rights to copy,
** modify and redistribute granted by the license, users are provided only
** with a limited warranty  and the software's author,  the holder of the
** economic rights,  and the successive licensors  have only  limited
** liability.
**
** In this respect, the user's attention is drawn to the risks associated
** with loading,  using,  modifying and/or developing or reproducing the
** software by the user in light of its specific status of free software,
** that may mean  that it is complicated to manipulate,  and  that  also
** therefore means  that it is reserved for developers  and  experienced
** professionals having in-depth computer knowledge. Users are therefore
** encouraged to load and test the software's suitability as regards their
** requirements in conditions enabling the security of their systems and/or
** data to be ensured and,  more generally, to use and operate it in the
** same conditions as regards security.
**
** The fact that you are presently reading this means that you have had
** knowledge of the CeCILL-C license and that you accept its terms.
**
****************************************************************************/

#include "database_settings.h"

#include "../core/abstract_cipher.h"

#include <QtCore/QSettings>
#include <QtSql/QSqlDatabase>

namespace qttools {

/*!
 * \class DatabaseSettings
 * \brief Settings to connect to a database. Settings can be loaded and saved from/to a QSettings
 *
 * \headerfile database_settings.h <qttools/sql/database_settings.h>
 * \ingroup qttools_sql
 */

DatabaseSettings::DatabaseSettings()
  : m_port(0)
{
}

/*! \sa QSqlDatabase::setHostName()
 */
void DatabaseSettings::setHost(const QString& host)
{
  m_host = host;
}

/*! \sa QSqlDatabase::hostName()
 */
QString DatabaseSettings::host() const
{
  return m_host;
}

/*! \sa QSqlDatabase::setDatabaseName()
 */
void DatabaseSettings::setDatabaseName(const QString& dbName)
{
  m_dbName = dbName;
}

/*! \sa QSqlDatabase::databaseName()
 */
QString DatabaseSettings::databaseName() const
{
  return m_dbName;
}

/*! \sa QSqlDatabase::setPort()
 */
void DatabaseSettings::setPort(int port)
{
  m_port = port;
}

/*! \sa QSqlDatabase::port()
 */
int DatabaseSettings::port() const
{
  return m_port;
}

/*! \sa QSqlDatabase::setUserName()
 */
void DatabaseSettings::setUserName(const QString& userName)
{
  m_userName = userName;
}

/*! \sa QSqlDatabase::userName()
 */
QString DatabaseSettings::userName() const
{
  return m_userName;
}

/*! \sa QSqlDatabase::setPassword()
 */
void DatabaseSettings::setPassword(const QString& password)
{
  m_password = password;
}

/*! \sa QSqlDatabase::password()
 */
QString DatabaseSettings::password() const
{
  return m_password;
}

/*! \brief Load settings from the persistent storage
 *  \param passwordCipher Encrypt/decrypt algorithm used to decrypt the password. If \c null then
 *         the default password is returned (see parameter \p defValues)
 *  \param defValues Default values when all or some persistent settings could not be retrieved
 */
void DatabaseSettings::load(const QSettings* settings,
                            const AbstractCipher* passwordCipher,
                            const ValuesHash& defValues)
{
  if (settings == NULL)
    return;

  const QString defHost = defValues.value("host").toString();
  const QString defDbName = defValues.value("name").toString();
  const int defPort = defValues.value("port").toInt();
  const QString defUser = defValues.value("user").toString();
  const QString defPwd = defValues.value("password").toString();

  this->setHost(settings->value("database/host", defHost).toString());
  this->setDatabaseName(settings->value("database/name", defDbName).toString());
  this->setPort(settings->value("database/port", defPort).toInt());
  this->setUserName(settings->value("database/user", defUser).toString());

  if (passwordCipher != NULL && settings->contains("database/password")) {
    const QByteArray decryptedPwd =
        passwordCipher->decrypted(settings->value("database/password").toByteArray());
    this->setPassword(decryptedPwd);
  }
  else {
    this->setPassword(defPwd);
  }
}

/*! \brief Write settings to persistent storage
 *  \param passwordCipher Encrypt/decrypt algorithm used to encrypt the password. If \c null then an
 *         empty password is stored. Otherwise the password() is reprensented as a UTF-8 byte array
 *         and passed to AbstractCipher::encrypted()
 */
void DatabaseSettings::write(QSettings* settings,
                             const AbstractCipher* passwordCipher) const
{
  if (settings == NULL)
    return;

  settings->setValue("database/host", this->host());
  settings->setValue("database/name", this->databaseName());
  settings->setValue("database/port", this->port());
  settings->setValue("database/user", this->userName());

  if (passwordCipher != NULL) {
    const QByteArray pwd = this->password().toUtf8();
    settings->setValue("database/password", passwordCipher->encrypted(pwd));
  }
  else {
    settings->setValue("database/password", QString());
  }
}

/*! \brief Apply the current settings to a QSqlDatabase instance
 *  \note It does not close/open the connection of \p db
 */
void DatabaseSettings::applyTo(QSqlDatabase* db) const
{
  if (db != NULL) {
    db->setDatabaseName(this->databaseName());
    db->setHostName(this->host());
    db->setPort(this->port());
    db->setUserName(this->userName());
    db->setPassword(this->password());
  }
}

} // namespace qttools
