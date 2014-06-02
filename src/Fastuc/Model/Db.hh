<?hh
namespace Fastuc\Model;

/**
 * Base class for those models that interacts with a MySQL database.
 */
class Db 
{
	/**
	 * @var mysqli
	 */
	protected \mysqli $db;

	/**
	 * @param \mysqli $db
	 */
	public function __construct( \mysqli $db )
	{
		$this->db = $db;
	}

	/**
	 * @param string $sql
	 */
	public function query( string $sql )
	{
		$result = $this->db->query( $sql );
		if( false === $result )
		{
			throw new Exception( $this->db, 'Unable to run query: ' . $this->db->error );
		}

		return $result;
	}

	/**
	 * @param string $sql
	 * @throws \Fastuc\Model\Exception
	 */
	public function prepareStatement( string $sql )
	{
		$stmt = $this->db->prepare( $sql );
		if( false === $stmt )
		{
			throw new Exception( $this->db );
		}
		return $stmt;
	}

	/**
	 * @throws \Fastuc\Model\Exception If the statement can not be executed.
	 * @param \mysqli_stmt $stmt Statement to be executed.
	 * @param bool $closeAfterwards Indicated whether the statement has to be closed immediately after execution.
	 * @return integer Number of affected rows.
	 */
	protected function execute( \mysqli_stmt $stmt, bool $closeAfterwards = true ) : int
	{
		$result = $stmt->execute();
		$affectedRows = $stmt->affected_rows;
		$error = $stmt->error;

		if( true === $closeAfterwards ) $stmt->close();

		if( false === $result )
		{
			throw new Exception( $this->db, $error );
		}

		return $affectedRows;
	}

	/**
	 * @param \mysqli_result $rs
	 * @param integer $index
	 * @return mixed
	 */
	public function fetchColumn( \mysqli_result $rs, int $index = 0 ) : mixed
	{
		$column = false;

		$row = $rs->fetch_row();
		if( false !== $row )
		{
			$column = isset( $row[ $index ] ) ? $row[ $index ] : null;
		}
		$rs->close();

		return $column;
	}

	/**
	 * @param \mysqli_stmt $stmt
	 * @return array
	 */
	public function fetchResult( \mysqli_stmt $stmt )
	{
		$results = $this->fetchAll( $stmt );
		if( false === $results )
			return false;

		if( 0 === count( $results ) )
			return null;

		return $results[0];
	}

	/**
	 * This method returns a resultset iterator that does not load all data in memory at once.
	 *
	 * @param \mysqli_stmt $stmt
	 * @return \Fastuc\Db\ResultSet
	 */
	public function getResultSet( \mysqli_stmt $stmt ) : \Fastuc\Db\ResultSet
	{
		return new \Fastuc\Db\ResultSet( $this->db, $stmt );
	}

	/**
	 * @deprecated
	 * @param \mysqli_stmt $stmt
	 * @see \Fastuc\Model\Db::getResultSet()
	 * @return array
	 */
	public function fetchAll( \mysqli_stmt $stmt )
	{
		$results = array();

		if( false === $stmt->execute() )
		{
			return false;
		}

		$stmt->store_result();

		$columnValues = array();
		$data = array();
		$meta = $stmt->result_metadata();

		while( $field = $meta->fetch_field() )
		{
			$columnValues[] = &$data[ $field->name ];
		}
		
		call_user_func_array( array( $stmt, 'bind_result' ), $columnValues );

		$i = 0;
                while( $stmt->fetch() )
		{   
			$results[$i] = array();
			foreach( $data as $columnName => $columnValue )
			{
				$results[ $i ][ $columnName ] = $columnValue;
			}
			$i++;
                }

		$stmt->free_result();

                return $results;
        }   
}

