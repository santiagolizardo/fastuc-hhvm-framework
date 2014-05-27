<?hh // strict
namespace Fastuc\Xml;

class SimpleXMLExtendedTest extends \PHPUnit_Framework_TestCase
{
	public function testAddMethods()
	{
		$xml = new SimpleXMLExtended( '<items/>' );
		
		$item = array(
					'firstKey' => 'firstValue',
					'secondKey' => 'secondValue', 
					);
		$setOfItems = array(
						array(
							'firstSubKey' => 'firstSubValue',
							'secondSubKey' => 'secondSubValue',
							),
						array(
							'firstSubKey' => 'firstSubValue',
							'secondSubKey' => 'secondSubValue',
							),
					);
					
		$xml->addSimpleElement( $item, 'item' );
		$xml->addSetOfElements( $setOfItems, 'set', 'subitem' );
		
		$this->assertEquals( 'firstValue', (string) $xml->item[0]->firstKey );
		$this->assertEquals( 'secondValue', (string) $xml->item[0]->secondKey );
		$this->assertEquals( 'firstSubValue', (string) $xml->set->subitem[0]->firstSubKey );
		$this->assertEquals( 'secondSubValue', (string) $xml->set->subitem[0]->secondSubKey );
		$this->assertEquals( 'firstSubValue', (string) $xml->set->subitem[1]->firstSubKey );
		$this->assertEquals( 'secondSubValue', (string) $xml->set->subitem[1]->secondSubKey );
	}
	
	public function testAddCData()
	{
		$xml = new SimpleXMLExtended( '<items/>' );
		
		$node = $xml->addChild( 'item' );
		$node->item->key = NULL;
		$node->item->key->addCData( '<p>HELLO</p>' );
		
		$this->assertEquals( '<p>HELLO</p>', (string) $node->item->key );
	}
}
