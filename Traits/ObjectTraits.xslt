<?xml version="1.0" encoding="utf-8"?>
<?altova_samplexml file:///D:/Projects/dISToBJ/Test/BaseTypes.xml?>
<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:fn="http://www.w3.org/2005/02/xpath-functions" xmlns:xdt="http://www.w3.org/2005/02/xpath-datatypes">
	<xsl:output method="text"/>
	<xsl:output name="text-def" method="text"/>
	<xsl:output name="xml-def" method="xml" indent="yes"/>
	<xsl:variable name="tab1" select="'&#x9;'"/>
	<xsl:variable name="tab2" select="concat($tab1, '&#x9;')"/>
	<xsl:variable name="tab3" select="concat($tab2, '&#x9;')"/>
	<xsl:variable name="tab4" select="concat($tab3, '&#x9;')"/>
	<xsl:variable name="tab5" select="concat($tab4, '&#x9;')"/>
	<xsl:variable name="newLine1" select="'&#xA;'"/>
	<xsl:variable name="newLine2" select="concat($newLine1, '&#xA;')"/>
	<!--=======================================================================-->
	<!--header with guards ans includes -->
	<!--=======================================================================-->
	<xsl:template match="/">
		<xsl:variable name="file" select="replace(tokenize(base-uri(.), '/')[last()],'.xml','')"/>
		<xsl:variable name="guard" select="concat($file, 'H')"/>
		<!--<xsl:variable name="fn" select="concat('../Test/', $file, '.h')"/>-->
		<xsl:variable name="fn" select="replace(base-uri(.),'.xml' ,'.h')"/>
		<xsl:result-document href="{$fn}" format="text-def">
			<xsl:value-of select="concat('#ifndef ', $guard, $newLine1)"/>
			<xsl:value-of select="concat('#define ', $guard, $newLine2)"/>
			<xsl:value-of select="concat('#include &quot;Object.h&quot;', $newLine1)"/>
			<xsl:value-of select="concat('#include &quot;Traits.h&quot;', $newLine2)"/>
			<xsl:value-of select="concat('namespace srdev', $newLine1)"/>
			<xsl:value-of select="concat('{', $newLine1)"/>
			<xsl:apply-templates select="ObjectTypes/Object" mode="Traits"/>
			<xsl:value-of select="concat('}', $newLine2)"/>
			<xsl:value-of select="concat('#endif', $newLine1)"/>
		</xsl:result-document>
	</xsl:template>
	<!--=======================================================================-->
	<!--process an Object node -->
	<!--=======================================================================-->
	<xsl:template match="Object" mode="Traits">
		<xsl:variable name="category" select="@category"/>
		<xsl:variable name="name" select="@name"/>
		<xsl:variable name="id" select="@id"/>
		<xsl:value-of select="concat($tab1, 'namespace ', $category, $newLine1)"/>
		<xsl:value-of select="concat($tab1, '{', $newLine1)"/>
		<xsl:value-of select="concat($tab2, 'namespace ', $name, 'T', $newLine1)"/>
		<xsl:value-of select="concat($tab2, '{', $newLine1)"/>
		<xsl:apply-templates select="Base" mode="Traits"/>
		<xsl:apply-templates select="Property" mode="PropertyT"/>
		<xsl:value-of select="concat($tab3, 'struct ObjectT', $newLine1)"/>
		<xsl:value-of select="concat($tab3, '{', $newLine1)"/>
		<xsl:value-of select="concat($tab4, 'static String getCategory() { return &quot;', $category, '&quot;; }', $newLine1)"/>
		<xsl:value-of select="concat($tab4, 'static String getName() { return &quot;', $name, '&quot;; }', $newLine1)"/>
		<xsl:value-of select="concat($tab4, 'static UuId getTypeId() { static const UuId id = generateIdFromString(&quot;', $id, '&quot;); return id; }', $newLine1)"/>
		<xsl:value-of select="concat($tab3, '};', $newLine1)"/>
		<xsl:value-of select="concat($tab3, 'struct PropertiesT', $newLine1)"/>
		<xsl:value-of select="concat($tab3, '{', $newLine1)"/>
		<xsl:apply-templates select="Property" mode="using"/>
		<xsl:value-of select="concat($tab4, 'using List = std::tuple&lt;')"/>
		<xsl:apply-templates select="Property" mode="tuple"/>
		<xsl:value-of select="concat('&gt;;', $newLine1)"/>
		<xsl:value-of select="concat($tab4, 'enum { LastId = std::tuple_size&lt;List&gt;::value };', $newLine1)"/>
		<xsl:value-of select="concat($tab3, '};', $newLine1)"/>
		<xsl:value-of select="concat($tab3, 'using Traits = ObjectTraits&lt;ObjectT, BaseTraits, PropertiesT&gt;;', $newLine1)"/>
		<xsl:value-of select="concat($tab2, '}', $newLine1)"/>
		<xsl:value-of select="concat($tab2, '/*!', $newLine1)"/>
		<xsl:variable name="xml" select="concat('../Doc/Traits/', $name, '.xml')"/>
		<xsl:result-document href="{$xml}" format="xml-def">
			<xsl:copy-of select="."/>
		</xsl:result-document>
		<xsl:value-of select="concat($tab2, '\include ', $name, '.xml', $newLine1)"/>
		<xsl:variable name="cpp" select="concat('../Doc/Traits/', $name, '.cpp')"/>
		<xsl:variable name="object" select="concat($category, '::', $name)"/>
		<xsl:result-document href="{$cpp}" format="text-def">
			<xsl:variable name="varName" select="concat(translate(substring($name,1,1),'ABCDEFGHIJKLMNOPQRSTUVWXYZ','abcdefghijklmnopqrstuvwxyz'), substring($name,2,string-length($name)-1))"/>
			<xsl:value-of select="concat('srdev::Wrapper&lt;', $object, '&gt; ', $varName,' = ', $object, '::make();', $newLine2)"/>
			<xsl:apply-templates select="Property" mode="example">
				<xsl:with-param name="objVarName" select="$varName"/>
			</xsl:apply-templates>
		</xsl:result-document>
		<xsl:value-of select="concat($tab2, '\include ', $name, '.cpp', $newLine1)"/>
		<!--<xsl:value-of select="concat($tab2, '\endcode', $newLine1)"/>-->
		<xsl:value-of select="concat($tab2, '*/', $newLine1)"/>
		<xsl:value-of select="concat($tab2, 'using ', $name, ' = ', $name, 'T::Traits;', $newLine1)"/>
		<xsl:value-of select="concat($tab1, '}', $newLine1)"/>
		<xsl:value-of select="concat($tab1, '/// \copydoc ', $object, $newLine1)"/>
		<xsl:value-of select="concat($tab1, 'template&lt;&gt;', $newLine1)"/>
		<xsl:value-of select="concat($tab1, 'struct ObjectAccess&lt;', $object, '&gt; : public ObjectImpl&lt;', $object, '::BaseTraits&gt;', $newLine1)"/>
		<xsl:value-of select="concat($tab1, '{', $newLine1)"/>
		<xsl:apply-templates select="Property" mode="access">
			<xsl:with-param name="object" select="$object"/>
		</xsl:apply-templates>
		<xsl:value-of select="concat($tab1, '};', $newLine1)"/>
	</xsl:template>
	<!--=======================================================================-->
	<!--process the Base node -->
	<!--=======================================================================-->
	<xsl:template match="Base" mode="Traits">
		<xsl:variable name="category" select="@category"/>
		<xsl:variable name="name" select="@name"/>
		<xsl:variable name="base" select="concat($category, '::', $name)"/>
		<xsl:value-of select="concat($tab3, 'using BaseTraits = ', $base, ';', $newLine1)"/>
	</xsl:template>
	<!--=======================================================================-->
	<!--process an Property node for PropertyT -->
	<!--=======================================================================-->
	<xsl:template match="Property" mode="PropertyT">
		<xsl:variable name="type" select="@type"/>
		<xsl:variable name="name" select="@name"/>
		<xsl:variable name="default">
			<xsl:choose>
				<xsl:when test="@default = ''">
					<xsl:value-of select="concat(@type, '()')"/>
				</xsl:when>
				<xsl:otherwise>
					<xsl:value-of select="@default"/>
				</xsl:otherwise>
			</xsl:choose>
		</xsl:variable>
		<!--		<xsl:variable name="default" select="@default"/>
		<xsl:variable name="default" select="concat(@type, '()')"/>
-->
		<xsl:value-of select="concat($tab3, 'namespace ', $name, $newLine1)"/>
		<xsl:value-of select="concat($tab3, '{', $newLine1)"/>
		<xsl:value-of select="concat($tab4, 'struct PropertyT', $newLine1)"/>
		<xsl:value-of select="concat($tab4, '{', $newLine1)"/>
		<xsl:value-of select="concat($tab5, 'static String getName() { return &quot;', $name, '&quot;; }', $newLine1)"/>
		<xsl:value-of select="concat($tab5, 'static ValuePtr getDefaultValue() { return ', $type, 'Value::make(', $default, '); }', $newLine1)"/>
		<xsl:value-of select="concat($tab4, '};', $newLine1)"/>
		<xsl:value-of select="concat($tab4, 'using Traits = PropertyTraits&lt;PropertyT,', $type,', BaseTraits::Properties::LastId + ', position() -1 , ' &gt;;', $newLine1)"/>
		<xsl:value-of select="concat($tab3, '}', $newLine1)"/>
	</xsl:template>
	<!--=======================================================================-->
	<!--process an Property node for tuple -->
	<!--=======================================================================-->
	<xsl:template match="Property" mode="tuple">
		<xsl:variable name="name" select="@name"/>
		<xsl:value-of select="$name"/>
		<xsl:if test="position() != last()">
			<xsl:text>,</xsl:text>
		</xsl:if>
	</xsl:template>
	<!--=======================================================================-->
	<!--process an Property node for using -->
	<!--=======================================================================-->
	<xsl:template match="Property" mode="using">
		<xsl:variable name="name" select="@name"/>
		<xsl:value-of select="concat($tab4, 'using ', $name, ' = ', $name, '::Traits;', $newLine1)"/>
	</xsl:template>
	<!--=======================================================================-->
	<!--process an Property node for getter and setter -->
	<!--=======================================================================-->
	<xsl:template match="Property" mode="access">
		<xsl:param name="object"/>
		<xsl:variable name="type" select="@type"/>
		<xsl:variable name="name" select="@name"/>
		<xsl:value-of select="concat($tab2, $type, 'ValuePtr get', $name, '() const', $newLine1, $tab2, '{', $newLine1)"/>
		<xsl:value-of select="concat($tab3, 'auto property = getProperty(', $object, '::Properties::', $name, '::Id);', $newLine1)"/>
		<xsl:value-of select="concat($tab3, 'return property-&gt;getValue();', $newLine1)"/>
		<xsl:value-of select="concat($tab2, '}', $newLine1)"/>
		<xsl:value-of select="concat($tab2, 'void set', $name, '(', $type, 'ValuePtr value)', $newLine1, $tab2, '{', $newLine1)"/>
		<xsl:value-of select="concat($tab3, 'auto property = getProperty(', $object, '::Properties::', $name, '::Id);', $newLine1)"/>
		<xsl:value-of select="concat($tab3, 'property-&gt;setValue(value);', $newLine1)"/>
		<xsl:value-of select="concat($tab2, '}', $newLine1)"/>
		<!-- <xsl:value-of select="concat($tab2, 'ValuePtr get', $name, '() const { return dynamic_pointer_cast&lt;const ', $type, 'Value>(getProperty(', $object, '::Properties::', $name, '::Id)-&gt;getValue()); }', $newLine1)"/> -->
		<!--<xsl:value-of select="concat($tab2, 'void set', $name, '(ValuePtr value) { getProperty(', $object, '::Properties::', $name, '::Id)-&gt;setValue(value	); }', $newLine1)"/>-->
		<!-- <xsl:value-of select="concat($tab2, $type, ' get', $name, '() const { return dynamic_pointer_cast&lt;const ', $type, 'Value>(getProperty(', $object, '::Properties::', $name, '::Id)-&gt;getValue())-&gt;getValue(); }', $newLine1)"/>
		<xsl:value-of select="concat($tab2, 'void set', $name, '(const ', $type, '&amp; value) { getProperty(', $object, '::Properties::', $name, '::Id)-&gt;setValue(', $type, 'Value::make(value)); }', $newLine1)"/> -->
		<xsl:if test="position() != last()">
			<xsl:value-of select="$newLine1"/>
		</xsl:if>
	</xsl:template>
	<!--=======================================================================-->
	<!--process an Property node for example code -->
	<!--=======================================================================-->
	<xsl:template match="Property" mode="example">
		<xsl:param name="objVarName"/>
		<xsl:variable name="type" select="@type"/>
		<xsl:variable name="name" select="@name"/>
		<xsl:variable name="varName" select="concat(translate(substring($name,1,1),'ABCDEFGHIJKLMNOPQRSTUVWXYZ','abcdefghijklmnopqrstuvwxyz'), substring($name,2,string-length($name)-1))"/>
		<!--
		String name = objectType->getName();
		objectType->setName(name);
		-->
		<xsl:value-of select="concat($type, ' ', $varName, ' = ', $objVarName, '-&gt;get', $name, '();', $newLine1)"/>
		<xsl:value-of select="concat($objVarName, '-&gt;set', $name, '(', $varName, ');', $newLine1)"/>
		<xsl:if test="position() != last()">
			<xsl:value-of select="$newLine1"/>
		</xsl:if>
	</xsl:template>
	<!--=======================================================================-->
	<!-- -->
	<!--=======================================================================-->
	<xsl:template name="camelCaseWord">
		<xsl:param name="text"/>
		<xsl:value-of select="translate(substring($text,1,1),'ABCDEFGHIJKLMNOPQRSTUVWXYZ','abcdefghijklmnopqrstuvwxyz')"/>
		<xsl:value-of select="substring($text,2,string-length($text)-1)"/>
	</xsl:template>
</xsl:stylesheet>