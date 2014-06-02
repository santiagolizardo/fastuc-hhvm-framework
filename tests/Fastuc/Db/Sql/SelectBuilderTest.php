<?hh // strict
namespace Fastuc\Db\Sql;

class SelectBuilderTest extends \PHPUnit_Framework_TestCase
{
	public function testSelectColumns()
	{
		$sqlBuilder = new SelectBuilder( 'user' );
		$sql = $sqlBuilder->build();

		$this->assertEquals( 'user', $sqlBuilder->getTableName() );
		$this->assertEquals( 'SELECT * FROM user', $sql );

		$sql = $sqlBuilder->addColumn( 'name' )->addColumns( 'email', 'age' )->build();

		$this->assertEquals( array( 'name', 'email', 'age' ), $sqlBuilder->getColumns() );
		$this->assertEquals( 'SELECT name, email, age FROM user', $sql );
	}

	public function testBuild()
	{
		$sqlbuilder = new SelectBuilder( 'testTable' );
		$sqlbuilder->addColumns( 'testColumn' );
		$sqlbuilder->addWhere( 'testColumn = testValue' );
		$sqlbuilder->setOffsetLimit( 0, 10 );
		
		$sql = $sqlbuilder->build();
		
		$this->assertFalse( strpos( $sql, 'invalidColumn' ) );
		$this->assertEquals( 0, strpos( $sql, 'SELECT testColumn' ) );
		$this->assertNotEquals( 0, strpos( $sql, 'FROM testTable' ) );
		$this->assertNotEquals( 0, strpos( $sql, 'WHERE testColumn = testValue' ) );
		$this->assertNotEquals( 0, strpos( $sql, 'LIMIT 0, 10' ) );
	}
}

