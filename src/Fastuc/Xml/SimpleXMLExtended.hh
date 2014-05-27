<?hh // strict
namespace Fastuc\Xml;

/*
 * Extension for SimpleXMLElement in order to add CDATA values in xml file
*/
Class SimpleXMLExtended extends \SimpleXMLElement
{
	/**
	 * @param string $cdataText
	 */
 	public function addCData( string $cdataText ) : void
	{
		$node = dom_import_simplexml( $this );
		$no = $node->ownerDocument;
		$node->appendChild( $no->createCDATASection( $cdataText ) );
	}

	/**
	 * @param array $data
	 * @param string $elementName
	 */
	public function addSimpleElement( array $data, string $elementName ) : void
	{
		$elementNode = $this->addChild( $elementName );
		foreach( $data as $elementKey => $elementValue )
		{
			if( preg_match( '/[<*>{*}]/', $elementValue ) )
			{
				$elementNode->$elementKey = NULL;
				$elementNode->$elementKey->addCData( $elementValue );
			}
			else
			{
				$elementNode->addChild( $elementKey, $elementValue );
			}
		}
	}

	/**
	 * @param array $data
	 * @param string $elementsName
	 * @param string $singleElementName
	 */
	public function addSetOfElements( array $data, string $elementsName, string $singleElementName ) : void
	{
		$elementsNode = $this->addChild( $elementsName );
		foreach( $data as $elementsData )
		{
			$elementNode = $elementsNode->addChild( $singleElementName );
			foreach( $elementsData as $elementKey => $elementValue )
			{
				if( preg_match( '/[<*>{*}]/', $elementValue ) )
				{
					$elementNode->$elementKey = NULL;
					$elementNode->$elementKey->addCData( $elementValue );
				}
				else
				{
					$elementNode->addChild( $elementKey, $elementValue );
				}
			}
		}
	}
}

