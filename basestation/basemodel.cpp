#include "basemodel.h"
#include <QDebug>
//返回数据的行数

int BaseModel::rowCount( const QModelIndex &parent ) const
{
if (parent.isValid())
return 0;
return baseInfos.size();
}


//返回数据的列数
int BaseModel::columnCount( const QModelIndex &parent ) const
{
if (parent.isValid())
return 0;
return totalColumn;
}

QVariant BaseModel::data( const QModelIndex &index, int role ) const
{
if (role == Qt::DisplayRole)
{
    if (index.column() == 1)
    return QString::number(index.row()+1);
    if (index.column() == 2)
    return baseInfos[index.row()].GetbaseID();
    if (index.column() == 3)
    return baseInfos[index.row()].GetbaseMac();
    if (index.column() == 4)
    return baseInfos[index.row()].GetbaseType();
    if (index.column() == 5)
    return baseInfos[index.row()].GetbaseX();
    if (index.column() == 6)
    return baseInfos[index.row()].GetbaseY();
    if (index.column() == 7)
    return baseInfos[index.row()].GetbaseZ();
    if (index.column() == 8)
    return baseInfos[index.row()].GetbaseRemark();
}
if (index.column()==0)
{
    if (role == Qt::CheckStateRole) {
       if(rowCheckStateMap.contains(index.row()))
       return rowCheckStateMap[index.row()] == Qt::Checked ? Qt::Checked :
       Qt::Unchecked; return Qt::Unchecked;
        }
}
return QVariant();
}


QVariant BaseModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
{
    if (section == 0)
    return QStringLiteral("多选");
    if (section == 1)
    return QStringLiteral("序号");
    if (section == 2)
    return QStringLiteral("基站ID");
    if (section == 3)
    return QStringLiteral("基站Mac");
    if (section == 4)
    return QStringLiteral("基站类型");
    if (section == 5)
    return QStringLiteral("基站X坐标");
    if (section == 6)
    return QStringLiteral("基站Y坐标");
    if (section == 7)
    return QStringLiteral("基站Z坐标");
    if (section == 8)
    return QStringLiteral("基站备注");
}
return QVariant();
}


Qt::ItemFlags BaseModel::flags( const QModelIndex &index ) const
{
    if
    (!index.isValid())
    return 0;
    if (index.column() == 0)
    //if (index.column() == colNumberWithCheckBox)
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;

    return  Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}


bool BaseModel::setData( const QModelIndex &index, const QVariant &value, int role )
{
    if(!index.isValid())
        return false;
   if (role == Qt::CheckStateRole && index.column() == 0)
   //if (role == Qt::CheckStateRole && index.column() == colNumberWithCheckBox)
    {
        if (value == Qt::Checked)
        {
            rowCheckStateMap[index.row()] = Qt::Checked;
            if(baseInfos.size() > index.row())
            emit BaseInfoIsChecked(baseInfos[index.row()]);
        }
        else
        {
            rowCheckStateMap[index.row()] = Qt::Unchecked;
        }
    }
    return true;
}


void BaseModel:: removeRow(int row){
    baseInfos.erase(baseInfos.begin()+row);
    //rowCheckStateMap.remove(row);

}


void BaseModel::AddBaseInfo( const BaseInfo &baseInfo )
{
baseInfos.push_back(baseInfo);  //把基站信息加入到要baseInfos容器中。
beginResetModel(); //开始初始化BaseModel，接着QTableView将重新显示
endResetModel(); //显示baseInfo容器中的学生信息
}


  void BaseModel::freshModel(){
      beginResetModel();
      endResetModel();
  }




