<?hh // strict
namespace Fastuc\Testing;

/**
 * Disables foreign key checks temporarily.
 */
class TruncateOperation extends \PHPUnit_Extensions_Database_Operation_Truncate
{
	/**
	 * @param \PHPUnit_Extensions_Database_DB_IDatabaseConnection $connection
	 * @param \PHPUnit_Extensions_Database_DataSet_IDataSet $dataSet
	 */
	public function execute( \PHPUnit_Extensions_Database_DB_IDatabaseConnection $connection, \PHPUnit_Extensions_Database_DataSet_IDataSet $dataSet )
	{
		$connection->getConnection()->query( 'SET foreign_key_checks = FALSE' );
		parent::execute( $connection, $dataSet );
		$connection->getConnection()->query( 'SET foreign_key_checks = TRUE' );
	}
}


