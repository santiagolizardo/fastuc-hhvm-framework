<?hh // strict
namespace Fastuc\Db\Sql;

class InsertBuilderTest extends \PHPUnit_Framework_TestCase
{
	public function testBuildInsert()
	{
		$sqlBuilder = new InsertBuilder( 'book' );
		$sqlBuilder->addColumns( 'isbn' );
		$sqlBuilder->addValue( '?' );
		
		$sql = $sqlBuilder->build();

		$this->assertEquals( 'book', $sqlBuilder->getTableName() );
		$this->assertContains( 'INSERT INTO book ( isbn ) VALUES ( ? )', $sql );
	}
}

