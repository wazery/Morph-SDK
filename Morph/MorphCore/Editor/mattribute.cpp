#include "mattribute.h"

using namespace Morph;

bool MAttribute::setValueByString(const MString &valueStr)
{
    return _setValueByString(mValue, valueStr);
}

bool MAttribute::_setValueByString(boost::any &dstValue, const MString &valueStr)
{
    try
    {
        if (dstValue.empty())
            return false;

        string valueString = valueStr.toUtf8().constData();

        if(dstValue.type() == typeid(int))
        {
            int v = boost::lexical_cast<int>(valueString);
            dstValue = v;
        }
        else if(dstValue.type() == typeid(unsigned int))
        {
            unsigned int v = boost::lexical_cast<unsigned int>(valueString);
            dstValue = v;
        }
        else if(dstValue.type() == typeid(long))
        {
            long v = boost::lexical_cast<long>(valueString);
            dstValue = v;
        }
        else if(dstValue.type() == typeid(unsigned long))
        {
            unsigned long v = boost::lexical_cast<unsigned long>(valueString);
            dstValue = v;
        }
        else if(dstValue.type() == typeid(float))
        {
            float v = boost::lexical_cast<float>(valueString);
            dstValue = v;
        }
        else if(dstValue.type() == typeid(MDegreeAngle))
        {
            MReal v = boost::lexical_cast<MReal>(valueString);
            dstValue = MDegreeAngle(v);
        }

        else if(dstValue.type() == typeid(MLimitFloat))
        {
            float v = boost::lexical_cast<float>(valueString);
            MLimitFloat limitFloat = boost::any_cast<MLimitFloat>(dstValue);
            if(v >= limitFloat.mMin && v<= limitFloat.mMax)
                limitFloat.mValue = v;
            dstValue = limitFloat;
        }
        else if(dstValue.type() == typeid(bool))
        {
            //bool v = boost::lexical_cast<bool>(valueString);
            if(valueString == "true" || valueString == "1" || valueString == "on" || valueString == "yes")
                dstValue = true;
            else if(valueString == "false" || valueString == "0"  || valueString == "off"  || valueString == "no")
                dstValue = false;
            else
            {
                MLogManager::getSingleton().logOutput(("ERROR: MAttribute::convertMStringToValue ,input syntax error."), M_ERROR);
                    return false;
            }
            //dstValue = v;
        }
        else if(dstValue.type() == typeid(MString))
        {
            dstValue = valueStr;
        }
        else if(dstValue.type() == typeid(MEnumList))
        {
            // FIXME: needs some refactoring.
            MString valueString = MString::fromUtf8(trim(valueStr.toUtf8().constData()).c_str());
            MEnumList enumList = boost::any_cast<MEnumList>(dstValue);
            // if found
            if(std::find(enumList.mStringList.begin(),enumList.mStringList.end(),valueString) != enumList.mStringList.end())
            {
                // change the select string;
                enumList.mStrSelected = valueString;
                dstValue = enumList;
            }
            else
            {
                MLogManager::getSingleton().logOutput(("ERROR: MAttribute::setValueByString input syntax error,not not found the string in the enumList.") + valueString, M_ERROR);
                return false;
            }
        }
        else if(dstValue.type() == typeid(MVector2))
        {

            MVector2 vec;
            vector<string> split_str_list ;
            split_str_list = tokenize(valueString," ,", true, false, "");

            if(split_str_list.size()==2)
            {
                vec.x = boost::lexical_cast<MReal>(split_str_list[0]);
                vec.y = boost::lexical_cast<MReal>(split_str_list[1]);
                dstValue = vec;
            }
            else
            {
                //dstValue = MVector2::ZERO;
                MLogManager::getSingleton().logOutput(("ERROR: MAttribute::setValueByString input syntax error, you should input 2 MVector2 value"), M_ERROR);
                    return false;
            }
        }
        else if(dstValue.type() == typeid(MVector3))
        {

            MVector3 vec;
            vector<string> split_str_list ;
            split_str_list = tokenize(valueString," ,", true, false, "");

            if(split_str_list.size()==3)
            {
                vec.x = boost::lexical_cast<MReal>(split_str_list[0]);
                vec.y = boost::lexical_cast<MReal>(split_str_list[1]);
                vec.z = boost::lexical_cast<MReal>(split_str_list[2]);
                dstValue = vec;
            }
            else
            {
                //dstValue = MVector3::ZERO;
                MLogManager::getSingleton().logOutput(("ERROR: MAttribute::setValueByString input syntax error, you should input 3 MVector3 value"), M_ERROR);
                    return false;
            }
        }
        else if(dstValue.type() == typeid(MVector4))
        {

            MVector4 vec;
            vector<string> split_str_list ;
            split_str_list = tokenize(valueString," ,", true, false, "");

            if(split_str_list.size()==4)
            {
                vec.x = boost::lexical_cast<MReal>(split_str_list[0]);
                vec.y = boost::lexical_cast<MReal>(split_str_list[1]);
                vec.z = boost::lexical_cast<MReal>(split_str_list[2]);
                vec.w = boost::lexical_cast<MReal>(split_str_list[3]);
                dstValue = vec;
            }
            else
            {
                //dstValue = MVector4::ZERO;
                MLogManager::getSingleton().logOutput(("ERROR: MAttribute::setValueByString input syntax error, you should input 4 MVector4 value"), M_ERROR);
                    return false;
            }
        }
        else if(dstValue.type() == typeid(MMatrix3))
        {

            MReal m[9];
            vector<string> split_str_list ;
            split_str_list = tokenize(valueString," ,", true, false, "");

            if(split_str_list.size()==9)
            {
                m[0] = boost::lexical_cast<MReal>(split_str_list[0]);
                m[1] = boost::lexical_cast<MReal>(split_str_list[1]);
                m[2] = boost::lexical_cast<MReal>(split_str_list[2]);
                m[3] = boost::lexical_cast<MReal>(split_str_list[3]);
                m[4] = boost::lexical_cast<MReal>(split_str_list[4]);
                m[5] = boost::lexical_cast<MReal>(split_str_list[5]);
                m[6] = boost::lexical_cast<MReal>(split_str_list[6]);
                m[7] = boost::lexical_cast<MReal>(split_str_list[7]);
                m[8] = boost::lexical_cast<MReal>(split_str_list[8]);

                MMatrix3 mat(m[0],m[1],m[2],m[3],m[4],m[5],m[6],m[7],m[8]);
                dstValue = mat;
            }
            else
            {
                //dstValue = MMatrix3::IDENTITY;
                MLogManager::getSingleton().logOutput(("ERROR: MAttribute::setValueByString input syntax error, you should input 3x3 matrix value"), M_ERROR);
                    return false;
            }
        }
        else if(dstValue.type() == typeid(MVector4))
        {

            MReal m[16];
            vector<string> split_str_list ;
            split_str_list = tokenize(valueString," ,", true, false, "");

            if(split_str_list.size()==16)
            {
                m[0] = boost::lexical_cast<MReal>(split_str_list[0]);
                m[1] = boost::lexical_cast<MReal>(split_str_list[1]);
                m[2] = boost::lexical_cast<MReal>(split_str_list[2]);
                m[3] = boost::lexical_cast<MReal>(split_str_list[3]);
                m[4] = boost::lexical_cast<MReal>(split_str_list[4]);
                m[5] = boost::lexical_cast<MReal>(split_str_list[5]);
                m[6] = boost::lexical_cast<MReal>(split_str_list[6]);
                m[7] = boost::lexical_cast<MReal>(split_str_list[7]);
                m[8] = boost::lexical_cast<MReal>(split_str_list[8]);
                m[9] = boost::lexical_cast<MReal>(split_str_list[9]);
                m[10] = boost::lexical_cast<MReal>(split_str_list[10]);
                m[11] = boost::lexical_cast<MReal>(split_str_list[11]);
                m[12] = boost::lexical_cast<MReal>(split_str_list[12]);
                m[13] = boost::lexical_cast<MReal>(split_str_list[13]);
                m[14] = boost::lexical_cast<MReal>(split_str_list[14]);
                m[15] = boost::lexical_cast<MReal>(split_str_list[15]);


                MMatrix4 mat(m[0],m[1],m[2],m[3],m[4],m[5],m[6],m[7],m[8],m[9],m[10],m[11],m[12],m[13],m[14],m[15]);
                dstValue = mat;
            }
            else
            {
                //dstValue = MMatrix4::IDENTITY;
                MLogManager::getSingleton().logOutput(("ERROR: MAttribute::setValueByString input syntax error, you should input 4x4 matrix value"), M_ERROR);
                    return false;
            }
        }
        else if(dstValue.type() == typeid(MQuaternion))
        {

            MQuaternion quat;
            vector<string> split_str_list ;
            split_str_list = tokenize(valueString," ,", true, false, "");

            if(split_str_list.size()==4)
            {
                quat.x = boost::lexical_cast<MReal>(split_str_list[0]);
                quat.y = boost::lexical_cast<MReal>(split_str_list[1]);
                quat.z = boost::lexical_cast<MReal>(split_str_list[2]);
                quat.w = boost::lexical_cast<MReal>(split_str_list[3]);
                dstValue = quat;
            }
            else
            {
                //dstValue = MVector4::ZERO;
                MLogManager::getSingleton().logOutput(("ERROR: MAttribute::setValueByString input syntax error, you should input 4 MVector4 value"), M_ERROR);
                    return false;
            }
        }
        //MComboAttr
        else if(dstValue.type() == typeid(MComboAttr))
        {
            //string valueString = valueStr.toUtf8().constData());
            vector<MString> split_str_list ;
            vector<string> tmp;
            tmp = bracketSplit(trim(valueStr.toUtf8().constData()), ('{'), ('}'));
            string s;
            foreach (s, tmp)
            {
                split_str_list.push_back(MString::fromStdString(s));
            }

            MComboAttr comboAttr = getValue<MComboAttr>();
            if(comboAttr.mValueList.size() != split_str_list.size())
            {
                MLogManager::getSingleton().logOutput(("ERROR: MAttribute::setValueByString input syntax error, params number for MComboAttr not macth"), M_ERROR);
                return false;
            }
            std::map<MString, boost::any>::iterator it;
            it = comboAttr.mValueList.begin();
            for(size_t i=0; i < split_str_list.size(); i++)
            {
                if(!_setValueByString(it->second, split_str_list[i]))
                {
                    MLogManager::getSingleton().logOutput(("ERROR: MAttribute::setValueByString input syntax error, on MComboAttr"), M_ERROR);
                    return false;
                }
                it++;
            }

            dstValue = comboAttr;
        }
        else if(dstValue.type() == typeid(MColor))
        {
            MColor bgColor;
            vector<string> split_str_list ;
            split_str_list = tokenize(valueString," ,", true, false, "");

            if(split_str_list.size()==4)
            {
                bgColor.r = boost::lexical_cast<MReal>(split_str_list[0]);
                bgColor.g = boost::lexical_cast<MReal>(split_str_list[1]);
                bgColor.b = boost::lexical_cast<MReal>(split_str_list[2]);
                bgColor.a = boost::lexical_cast<MReal>(split_str_list[3]);
            }
            else if(split_str_list.size()==3)
            {
                bgColor.r = boost::lexical_cast<MReal>(split_str_list[0]);
                bgColor.g = boost::lexical_cast<MReal>(split_str_list[1]);
                bgColor.b = boost::lexical_cast<MReal>(split_str_list[2]);
                bgColor.a = 1.0;
            }
            else
            {
                MLogManager::getSingleton().logOutput(("ERROR: MAttribute::setValueByString input syntax error, you should input 3 or 4 colour value[0.0 ~ 1.0]"), M_ERROR);
                    return false;
            }
            if(bgColor.r > 1.0 || bgColor.r < 0.0 || bgColor.g > 1.0 || bgColor.g < 0.0 || bgColor.b > 1.0 || bgColor.b < 0.0 || bgColor.a > 1.0 || bgColor.a < 0.0)
            {
                MLogManager::getSingleton().logOutput(("ERROR: MAttribute::setValueByString input syntax error, you should input colour value betMeen[0.0 ~ 1.0]"), M_ERROR);
                    return false;
            }

            dstValue = bgColor;
        }
        else
        {
            MLogManager::getSingleton().logOutput(("ERROR: MAttribute::convertMStringToValue, input attribute type not suport."), M_ERROR);
            return false;
        }
    }
    catch (boost::bad_lexical_cast &e)
    {
        MLogManager::getSingleton().logOutput("ERROR: MAttribute::convertMStringToValue " + MString::fromUtf8(std::string(e.what()).c_str()), M_ERROR);
        return false;
    }
    return true;
}

typedef basic_string<char>::size_type S_T;
static const S_T npos = -1;
vector<string> MAttribute::tokenize(const string& src, string tok, bool trim, bool quote, string null_subst)
{
    vector<string> v;
    if( src.empty() || tok.empty() ) return v;

    S_T pre_index = 0, index = 0, len = 0;
    while( (index = src.find_first_of(tok, pre_index)) != npos )
    {
        if(quote && src.at(pre_index)=='\"')
        {
            index = src.find_first_of("\"", pre_index+1);
            if(index == npos)
                break;
            else
                v.push_back(src.substr(pre_index+1, index-pre_index-1));

            if((index+1)==src.size())
                break;
            pre_index = index+1;

            index = src.find_first_of(tok, pre_index);
            if(pre_index == index)
                pre_index = index+1;

            continue;
        }
        //--------------------------------------------------
        if( (len = index-pre_index)!=0 ) v.push_back(src.substr(pre_index, len));
        else if(trim==false)
            v.push_back(null_subst);
        pre_index = index+1;
    }
    string endstr = src.substr(pre_index);
    if( trim==false ) v.push_back( endstr.empty()?  null_subst:endstr );
    else if(!endstr.empty() ) v.push_back(endstr);
    return v;
}

vector<string> MAttribute::bracketSplit(const string& src, char beginChar, char endChar)
{
    vector<char> beginCharList;

    vector<string> v;
    if( src.empty() || (beginChar == endChar))
        return v;

    S_T begin_index = -1, end_index = -1, len = 0;
    for(S_T i = 0;i<src.size();i++)
    {
        if(src.at(i) == beginChar)
        {
            beginCharList.push_back(beginChar);
            if(beginCharList.size() == 1)
                begin_index = i;
        }

        if(src.at(i) == endChar)
        {
            if(beginCharList.empty())
                continue;
            beginCharList.pop_back();
            if(beginCharList.empty())
            {
                end_index = i;
                len = (end_index) - (begin_index + 1);
                if(len>0)
                v.push_back(src.substr(begin_index + 1, len));
            }
        }
    }
    return v;
}

MString MAttribute::getValuetoString() const
{
    return _getValueToString(mValue);
}

MString MAttribute::_getValueToString(const boost::any &srcValue) const
{
    MString result = "";

    try{
        if(srcValue.empty())// if the pAttr is NULL,MAKE a Marn!
            return "";

        if(srcValue.type() == typeid(int))
        {

            int value = boost::any_cast<int>(srcValue);
            stringstream stream;
            stream<<value;
            result = MString::fromUtf8(stream.str().c_str());
        }
        else if(srcValue.type() == typeid(unsigned int))
        {
            unsigned int value = boost::any_cast<unsigned int>(srcValue);
            stringstream stream;
            stream<<value;
            result = MString::fromUtf8(stream.str().c_str());
        }
        else if(srcValue.type() == typeid(long))
        {
            long value = boost::any_cast<long>(srcValue);
            stringstream stream;
            stream<<value;
            result = MString::fromUtf8(stream.str().c_str());
        }
        else if(srcValue.type() == typeid(unsigned long))
        {
            unsigned long value = boost::any_cast<unsigned long>(srcValue);
            stringstream stream;
            stream<<value;
            result = MString::fromUtf8(stream.str().c_str());
        }
        else if(srcValue.type() == typeid(unsigned short))
        {
            unsigned short value = boost::any_cast<unsigned short>(srcValue);
            stringstream stream;
            stream<<value;
            result = MString::fromUtf8(stream.str().c_str());
        }
        else if(srcValue.type() == typeid(MDegreeAngle))
        {

            MDegreeAngle value = boost::any_cast<MDegreeAngle>(srcValue);
            stringstream stream;
            stream<<value.valueDegrees();
            result = MString::fromUtf8(stream.str().c_str());
        }
        else if(srcValue.type() == typeid(float))
        {
            float value = boost::any_cast<float>(srcValue);
            stringstream stream;
            stream<<value;
            result = MString::fromUtf8(stream.str().c_str());
        }
        else if(srcValue.type() == typeid(MLimitFloat))
        {
            MLimitFloat limitFloat = boost::any_cast<MLimitFloat>(srcValue);
            float value = limitFloat.mValue;
            stringstream stream;
            stream<<value;
            result = MString::fromUtf8(stream.str().c_str());
        }
        else if(srcValue.type() == typeid(bool))
        {
            bool value = boost::any_cast<bool>(srcValue);
            if(value)
                result = "true";
            else
                result = "false";
        }
        else if(srcValue.type() == typeid(MString))
        {
            result = boost::any_cast<MString>(srcValue);
        }
        else if(srcValue.type() == typeid(MEnumList))
        {

            MEnumList enumList = boost::any_cast<MEnumList>(srcValue);
            if(enumList.mStrSelected == "true" || enumList.mStrSelected == "on" || enumList.mStrSelected == "yes" ||enumList.mStrSelected == "1")
                result = "true";
            else if(enumList.mStrSelected == "false" || enumList.mStrSelected == "off" || enumList.mStrSelected == "no" || enumList.mStrSelected == "0")
                result = "false";
            else
                result = enumList.mStrSelected;
        }
        else if(srcValue.type() == typeid(MVector2))
        {
            MVector2 value = boost::any_cast<MVector2>(srcValue);
            stringstream stream;
            stream << value.x << " " << value.y;
            result = MString::fromUtf8(stream.str().c_str());

        }
        else if(srcValue.type() == typeid(MVector3))
        {
            MVector3 value = boost::any_cast<MVector3>(srcValue);
            stringstream stream;
            stream << value.x << " " << value.y << " " << value.z;
            result = MString::fromUtf8(stream.str().c_str());
        }
        else if(srcValue.type() == typeid(MVector4))
        {
            MVector4 value = boost::any_cast<MVector4>(srcValue);
            stringstream stream;
            stream << value.x << " " << value.y << " " << value.z << " " << value.w;
            result = MString::fromUtf8(stream.str().c_str());
        }
        else if(srcValue.type() == typeid(MColor))
        {
            MColor value = boost::any_cast<MColor>(srcValue);
            stringstream stream;
            stream << value.r << " " << value.g << " " << value.b << " " << value.a;
            result = MString::fromUtf8(stream.str().c_str());
        }
        else if(srcValue.type() == typeid(MMatrix3))
        {
            MMatrix3 val = boost::any_cast<MMatrix3>(srcValue);
            stringstream stream;
            stream << val[0][0] << " "
                << val[0][1] << " "
                << val[0][2] << " "
                << val[1][0] << " "
                << val[1][1] << " "
                << val[1][2] << " "
                << val[2][0] << " "
                << val[2][1] << " "
                << val[2][2];
            result = MString::fromUtf8(stream.str().c_str());
        }
        else if(srcValue.type() == typeid(MMatrix4))
        {
            MMatrix4 val = boost::any_cast<MMatrix4>(srcValue);
            stringstream stream;
            stream << val[0][0] << " "
                << val[0][1] << " "
                << val[0][2] << " "
                << val[0][3] << " "
                << val[1][0] << " "
                << val[1][1] << " "
                << val[1][2] << " "
                << val[1][3] << " "
                << val[2][0] << " "
                << val[2][1] << " "
                << val[2][2] << " "
                << val[2][3] << " "
                << val[3][0] << " "
                << val[3][1] << " "
                << val[3][2] << " "
                << val[3][3];
            result = MString::fromUtf8(stream.str().c_str());
        }
        else if(srcValue.type() == typeid(MQuaternion))
        {
            MQuaternion val = boost::any_cast<MQuaternion>(srcValue);
            stringstream stream;
            stream << val.x << " " << val.y << " " << val.z << " " << val.w;
            result = MString::fromUtf8(stream.str().c_str());

        }
        else if(srcValue.type() == typeid(MComboAttr))
        {
            MComboAttr comboAttr = boost::any_cast<MComboAttr>(srcValue);
            stringstream stream;

            std::map<MString,boost::any>::iterator it;
            for(it = comboAttr.mValueList.begin();it!=comboAttr.mValueList.end();it++)
            {
                MString val = this->_getValueToString(it->second);

                val = "{" + val + "}";//braces the string;
                if(it == comboAttr.mValueList.begin())
                    stream << val.toUtf8().constData();
                else
                    stream << " " << val.toUtf8().constData();

            }
            result = MString::fromUtf8(stream.str().c_str());

        }
        else
        {
            MLogManager::getSingleton().logOutput("ERROR:  MAttribute::converMStringToValue ,input attribute type not suport.", M_ERROR);
            return "";
        }
    }
    catch(boost::bad_lexical_cast& e)
    {
        MLogManager::getSingleton().logOutput("ERROR:  MAttribute::converMStringToValue " + MString::fromUtf8(std::string(e.what()).c_str()), M_ERROR);
            return "";
    }

    return result;
}

bool MAttribute::setValue(const boost::any &value)
{
    try
    {
        if(isEmpty())
        {
            mValue = value;
            return true;
        }
        else if(getType() == typeid(MEnumList) && value.type() == typeid(MString))
        {
            MString strValue = boost::any_cast<MString>(value);
            this->setValueByString(strValue);
            return true;
        }
        else if(getType() == typeid(MLimitFloat) && value.type() == typeid(float))
        {
            float input = boost::any_cast<float>(value);
            MLimitFloat limitFloat = this->getValue<MLimitFloat>();
            limitFloat.mValue = input;
            this->mValue = limitFloat;
            return true;
        }
        else if(getType() == typeid(MDegreeAngle) && (value.type() != typeid(MDegreeAngle)))
        {
            MReal input = 0.0;
            if(value.type() == typeid(float))
                input = boost::any_cast<float>(value);
            else if(value.type() == typeid(MReal))
                input = boost::any_cast<MReal>(value);
            else if(value.type() == typeid(int))
                input = boost::any_cast<int>(value);
            else if(value.type() == typeid(double))
                input = boost::any_cast<double>(value);
            else
            {
                MLogManager::getSingleton().logOutput("ERROR: MAttribute::setAnyValue >>MDegreeAngle>> dstValue.type() != typeid(T) ", M_ERROR);
                return false;
            }

            MDegreeAngle angle(input);

            this->mValue = angle;
            return true;
        }
        else if(getType() != value.type())
        {
            MLogManager::getSingleton().logOutput("ERROR: MAttribute::setAnyValue >> dstValue.type() != typeid(T) ", M_ERROR);
            return false;
        }

        mValue = value;

    }
    catch(boost::bad_lexical_cast& e)
    {
        MLogManager::getSingleton().logOutput("ERROR: MAttribute::setValue " + MString::fromUtf8(std::string(e.what()).c_str()), M_ERROR);
            return false;
    }
    return(true);
}

bool MAttribute::setDefaultValue(const boost::any &value)
{
    try
    {
        if(isEmpty())
        {
            mDefaultValue = value;
            return true;
        }
        else if(getType() == typeid(MEnumList) && value.type() == typeid(MString))
        {
            MString strValue = boost::any_cast<MString>(value);
            MEnumList v = this->getDefaultValue<MEnumList>();
            v.mStrSelected = strValue;
            mDefaultValue = v;
            return true;
        }
        else if(getType() == typeid(MLimitFloat) && value.type() == typeid(float))
        {
            float input = boost::any_cast<float>(value);
            MLimitFloat limitFloat = this->getDefaultValue<MLimitFloat>();
            limitFloat.mValue = input;
            this->mDefaultValue = limitFloat;
            return true;
        }
        else if(getType() == typeid(MDegreeAngle) && value.type() == typeid(float))
        {
            float input = boost::any_cast<float>(value);
            MDegreeAngle angle(input);

            this->mDefaultValue = angle;
            return true;
        }

        else if(getType() != value.type())
        {
            MLogManager::getSingleton().logOutput("ERROR: MAttribute::setAnyValue >> dstValue.type() != typeid(T) ", M_ERROR);
            return false;
        }

        mDefaultValue = value;

    }
    catch(boost::bad_lexical_cast& e)
    {
        MLogManager::getSingleton().logOutput("ERROR: MAttribute::setValue " + MString::fromUtf8(std::string(e.what()).c_str()), M_ERROR);
        return false;
    }
    return(true);
}
