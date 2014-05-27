<?hh // strict
namespace Fastuc\Testing;

class ArrayDataSetTest extends \PHPUnit_Framework_TestCase
{
	public function testArray()
	{
		$data = array(
			'game' => array(
				array(
					'id' => 1,
					'name' => 'Call of duty',
					'category' => 'FPS'
				)
			)
		);

		$this->setExpectedException( 'InvalidArgumentException', 'user is not a table in the current database' );

		$dataSet = new ArrayDataSet( $data );
		$dataSet->getTable( 'user' );
	}
}

