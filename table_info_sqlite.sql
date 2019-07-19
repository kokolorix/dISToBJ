SELECT m.name as tableName, p.name as columnName, p.type as dataType, p.dflt_value as defaultValue, p.pk as primaryKey
FROM sqlite_master m
left outer join pragma_table_info((m.name)) p
     on m.name <> p.name
where m.type = 'table'
order by tableName, columnName
;