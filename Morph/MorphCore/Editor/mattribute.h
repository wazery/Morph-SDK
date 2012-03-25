#ifndef MATTRIBUTE_H
#define MATTRIBUTE_H

#include "Ogre.h"
#include <QMap>

// FIXME: Need to be re-examined if we can use something else.
#include <boost/any.hpp>
#include <boost/lexical_cast.hpp>

#include "MType.h"
#include "MLogManager.h"

using namespace std;

namespace Morph
{

    typedef Ogre::ColourValue MColor;
    typedef Ogre::Vector2 MVector2;
    typedef Ogre::Vector3 MVector3;
    typedef Ogre::Vector4 MVector4;
    typedef Ogre::Matrix3 MMatrix3;
    typedef Ogre::Matrix4 MMatrix4;
    typedef Ogre::Quaternion MQuaternion;
    typedef Ogre::Real MReal;
    typedef Ogre::Degree MDegreeAngle;

    struct MLimitFloat
    {
        float mValue;
        float mMax;
        float mMin;
    };

    struct MEnumList
    {
        std::vector<MString> mStringList;
        MString mStrSelected;
    };

    struct MComboAttr
    {
        // <name, value>
        std::map<MString, boost::any> mValueList;
    };

    class MAttribute
    {
    public:
        MAttribute(const MString &name, const boost::any &value, const MString &description = "")
            :mName(name), mValue(value)
        {
            mDescription = "(" + name + ")" + description;
            mDefaultValue = value;
            mReadOnly = false;
        }

        MAttribute() {mName = ""; mReadOnly = false;}

        virtual bool setValueByString(const MString &valueStr);
        virtual MString getValuetoString() const;

        bool setValue(const boost::any &value);
        bool setDefaultValue(const boost::any &value);

        template<typename T>
        T getValue() const
        {
            try
            {
                if (getType() != typeid(T))
                {
                    MLogManager::getSingleton().logOutput("ERROR: MAttribute::getValue >> dstValue.type() != typeid(T)", M_ERROR);
                    return T();
                }
                T value = boost::any_cast<T> (mValue);
                return value;
            }

            //FIXME: find a relevant to boost:bad_lexical_cast
            catch (boost::bad_lexical_cast &e)
            {
                MLogManager::getSingleton().logOutput("ERROR: MAttribute::setValue " + MString::fromUtf8(std::string(e.what()).c_str()), M_ERROR);
                return T();
            }
        }

        template<typename T>
        T getDefaultValue() const
        {
            try
            {
                if (getType() != typeid(T))
                {
                    MLogManager::getSingleton().logOutput("ERROR: MAttribute::getValue >> dstValue.type() != typeid(T) ", M_ERROR);
                    return T();
                }
                T value = boost::any_cast<T> (mDefaultValue);
                return value;
            }
            catch (boost::bad_lexical_cast &e)
            {
                MLogManager::getSingleton().logOutput("ERROR: MAttribute::setValue " + MString::fromUtf8(std::string(e.what()).c_str()), M_ERROR);
                return T();
            }
        }

        const boost::any &getValue() const {return mValue;}

        bool isReadOnly() const {return mReadOnly;}
        void setReadOnly(bool readOnly) {mReadOnly = readOnly;}
        bool isEmpty() const {mValue.empty();}

        // Access the name
        const MString &getName() const {return mName;}
        void setName(MString &name) {mName = name;}

        // Access the description
        const MString &getDescription() const {return mDescription;}
        void setDescription(MString &description) {mDescription = description;}

        const type_info &getType() const {return mValue.type();}

        // Some Utility functions,
        vector<string> tokenize(const string &src, string tok, bool trim, bool quote, string null_subst);
        vector<string> bracketSplit(const string &src, char beginChar, char endChar);
        static string trim(const string &source, const string &t = " ")
        {
            string str = source;
            return trim_right(trim_left(str, t), t);
        }

        static string trim_right(const string &source, const string &t= " ")
        {
            string str = source;
            return str.erase(str.find_last_not_of(t)+1);
        }

        static string trim_left(const string &source, const string &t=" ")
        {
            string str = source;
            return str.erase(0,str.find_first_not_of(t));
        }
    protected:

        /** Converts the boost::any value to MString*/
        virtual MString _getValueToString(const boost::any &srcValue) const;

        /** Sets the boost::any value using MString*/
        virtual bool _setValueByString(boost::any &dstValue, const MString &valueStr);

        MString mName;
        boost::any mValue;
        MString mDescription;
        boost::any mDefaultValue;

        bool mReadOnly;
    };

    typedef QMap<MString, MAttribute> MAttributeList;
}
#endif // MATTRIBUTE_H
