<?hh // strict
namespace Fastuc\Model;

class DbTest extends \PHPUnit_Extensions_Database_TestCase
{
	public function getConnection()
	{
		$db = new \PDO( 'mysql:host=127.0.0.1;charset=utf8;dbname=fastuc_testdb', 'root', '' );
		return $this->createDefaultDBConnection( $db, 'fastuc_testdb' );
	}

	public function getDataSet()
	{
		return new \Fastuc\Testing\ArrayDataSet(
			array(
				'game' => array(
					array( 
						'id' => 1,
						'name' => 'Call of duty',
						'category' => 'FPS'
					)
				)
			)
		);
	}

	public function setUp()
	{
		parent::setup();

		$this->mysql = new \mysqli( '127.0.0.1', 'root', '', 'fastuc_testdb' );
		$this->model = new Db( $this->mysql );
	}

	public function tearDown()
	{
		$this->mysql->close();

		parent::tearDown();
	}	

	public function testQueryWrongSql()
	{
		$this->setExpectedException( '\Fastuc\Model\Exception', 'Unable to run query' );
		$sql = 'SELECT + FORM game';
		$this->model->query( $sql );
	}

	public function testAll()
	{
		$sql = 'SELECT id, name, category FROM game';
		$stmt = $this->model->prepareStatement( $sql );
		$this->assertEquals( array( array( 'id' => 1, 'name' => 'Call of duty', 'category' => 'FPS' ) ), $this->model->fetchAll( $stmt ) );
	}

	public function testSingle()
	{
		$sql = 'SELECT id, name, category FROM game WHERE id = ?';
		$id = 1;

		$game = array( 'id' => 1, 'name' => 'Call of duty', 'category' => 'FPS' );

		$stmt = $this->model->prepareStatement( $sql );
		$stmt->bind_param( 'i', $id );
		$this->assertEquals( $game, $this->model->fetchResult( $stmt ) );
	}

	public function testColumn()
	{
		$sql = 'SELECT name, category FROM game WHERE id = 1';
		$rs = $this->model->query( $sql );
		$this->assertEquals( 'Call of duty', $this->model->fetchColumn( $rs ) );
		
		$rs = $this->model->query( $sql );
		$this->assertEquals( 'FPS', $this->model->fetchColumn( $rs, 1 ) );

		$rs = $this->model->query( $sql );
		$this->assertNull( $this->model->fetchColumn( $rs, 2 ) );
	}
}

